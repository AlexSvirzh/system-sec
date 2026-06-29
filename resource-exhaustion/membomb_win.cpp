#include <windows.h>
#include <stdio.h>

int main() {
    SIZE_T allocation_size = 1ULL * 1024ULL * 1024ULL * 1024ULL;
    LPVOID memory_ptr;
    SYSTEM_INFO sysInfo;
    
    GetSystemInfo(&sysInfo);
    DWORD pageSize = sysInfo.dwPageSize;
    printf("System page size is: %lu bytes\n", pageSize);
    
    memory_ptr = VirtualAlloc(
        NULL,
        allocation_size,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE
    );
    
    if (memory_ptr == NULL) {
        printf("VirtualAlloc failed. Error code: %lu\n", GetLastError());
        return 1;
    }
    
    printf("Memory allocated at: %p. Touching pages...\n", memory_ptr);
    
    for (SIZE_T i = 0; i < allocation_size; i += pageSize) {
        ((char*)memory_ptr)[i] = 0;
    }
    
    printf("Memory has been touched. Process will now sleep for 60 seconds.\n");
    Sleep(60000); // Sleep for 60 seconds (60,000 milliseconds)
    
    VirtualFree(memory_ptr, 0, MEM_RELEASE);
    printf("Memory freed.\n");
    
    return 0;
}
