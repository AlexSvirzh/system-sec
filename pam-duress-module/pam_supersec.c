#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <syslog.h>
#include <unistd.h>
#define USB_KEY_PATH "/tmp/usb_key"
#define SECRET_DATA_DIR "/tmp/top_secret"
#define PANIC_SUFFIX "SOS"
int converse(pam_handle_t *pamh, int nargs, const struct pam_message
**message, struct pam_response **response) {
struct pam_conv *conv;
int retval = pam_get_item(pamh, PAM_CONV, (const void **)&conv);
if (retval != PAM_SUCCESS) return retval;
return conv->conv(nargs, message, response, conv->appdata_ptr);
}
PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int
argc, const char **argv) {
struct pam_message msg;
const struct pam_message *msgp;
struct pam_response *resp = NULL;
int retval;
FILE *fp;
char real_pin[64];
char panic_pin[128];
if (access(USB_KEY_PATH, F_OK) != 0) {
openlog("PAM-SECURE", LOG_PID, LOG_AUTH);
syslog(LOG_WARNING, "Authentication failed: Physical USB key
missing.");
closelog();
msg.msg_style = PAM_ERROR_MSG;
msg.msg = "ACCESS DENIED: Please insert Security USB Key!";
msgp = &msg;
10
struct pam_conv *conv;
pam_get_item(pamh, PAM_CONV, (const void **)&conv);
conv->conv(1, &msgp, &resp, conv->appdata_ptr);
return PAM_AUTH_ERR;
}
fp = fopen(USB_KEY_PATH, "r");
if (!fp) return PAM_AUTH_ERR;
if (fscanf(fp, "%63s", real_pin) != 1) {
fclose(fp);
return PAM_AUTH_ERR;
}
fclose(fp);
snprintf(panic_pin, sizeof(panic_pin), "%s%s", real_pin,
PANIC_SUFFIX);
msg.msg_style = PAM_PROMPT_ECHO_OFF;
msg.msg = "Enter Security PIN: ";
msgp = &msg;
struct pam_conv *conv;
retval = pam_get_item(pamh, PAM_CONV, (const void **)&conv);
if (retval != PAM_SUCCESS) return retval;
retval = conv->conv(1, &msgp, &resp, conv->appdata_ptr);
if (retval != PAM_SUCCESS || resp == NULL) return PAM_AUTH_ERR;
char *user_input = resp[0].resp;
if (strcmp(user_input, real_pin) == 0) {
free(resp[0].resp);
free(resp);
return PAM_SUCCESS;
}
else if (strcmp(user_input, panic_pin) == 0) {
free(resp[0].resp);
free(resp);
openlog("PAM-SECURE", LOG_PID | LOG_CONS, LOG_AUTH);
11
syslog(LOG_EMERG, "DURESS CODE ENTERED! Initiating emergency
wipe protocol.");
closelog();
char command[256];
snprintf(command, sizeof(command), "rm -rf %s",
SECRET_DATA_DIR);
system(command);
return PAM_SUCCESS;
}
free(resp[0].resp);
free(resp);
return PAM_AUTH_ERR;
}
PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc,
const char **argv) { return PAM_SUCCESS; }
PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc,
const char **argv) { return PAM_SUCCESS; }
PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int
argc, const char **argv) { return PAM_SUCCESS; }
PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int
argc, const char **argv) { return PAM_SUCCESS; }
PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc,
const char **argv) { return PAM_SUCCESS; }
