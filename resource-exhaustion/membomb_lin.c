#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    long long allocation_size = 3 * (1024LL * 1024LL * 1024LL);
    void *memory_ptr;
    long page_size = getpagesize();
    
    printf("Page size on this system is: %ld bytes\n", page_size);
    
    memory_ptr = mmap(NULL, allocation_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory_ptr == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }
    
    printf("Memory allocated at address: %p\n", memory_ptr);
    printf("Press Enter to start writing to memory...\n");
    getchar();
    
    for (long long i = 0; i < allocation_size; i += page_size) {
        ((char*)memory_ptr)[i] = 0;
    }
    
    printf("Memory has been touched. The process will now sleep for 60 seconds.\n");
    sleep(60);
    
    munmap(memory_ptr, allocation_size);
    printf("Memory freed.\n");
    
    return 0;
}
