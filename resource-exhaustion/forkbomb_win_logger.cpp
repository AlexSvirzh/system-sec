#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>

// Функция подсчета процессов
DWORD GetProcessCount() {
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) return 0;
    
    DWORD processCount = 0;
    if (Process32First(hProcessSnap, &pe32)) {
        do { 
            processCount++; 
        } while (Process32Next(hProcessSnap, &pe32));
    }
    
    CloseHandle(hProcessSnap);
    return processCount;
}

int main() {
    FILE* logfile = fopen("log.txt", "w");
    if (logfile == NULL) {
        printf("Error: Could not create log.txt\n");
        return 1;
    }
    
    fprintf(logfile, "ProcessCount\n");
    printf("Logging process count...\n");
    
    while (true) {
        DWORD count = GetProcessCount();
        fprintf(logfile, "%lu\n", count);
        fflush(logfile);
        Sleep(200);
    }
    
    fclose(logfile);
    return 0;
}
