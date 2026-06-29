#include <windows.h>
#include <stdio.h>

int main() {
    FILE* logfile = fopen("win_mem_log.csv", "w");
    if (logfile == NULL) {
        printf("Error: Could not create log file.\n");
        return 1;
    }
    
    fprintf(logfile, "Timestamp,FreeMemory_MB\n");
    printf("Starting memory monitoring... Press [CTRL+C] to stop.\n");
    
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    
    while (true) {
        if (GlobalMemoryStatusEx(&memInfo)) {
            DWORDLONG free_mem_mb = memInfo.ullAvailPhys / (1024 * 1024);
            SYSTEMTIME st;
            GetLocalTime(&st);
            
            fprintf(logfile, "%02d:%02d:%02d,%llu\n", st.wHour, st.wMinute, st.wSecond, free_mem_mb);
            fflush(logfile);
        }
        Sleep(2000);
    }
    
    fclose(logfile);
    return 0;
}
