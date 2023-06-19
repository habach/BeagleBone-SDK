#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 256

int main() {
    const int SIZE = 4096;
    const char *name = "OS";

    int shm_fd;

    void *ptr;

    char url[MEM_SIZE];

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    ftruncate(shm_fd, SIZE);

    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // mmap_read(shm_fd, ptr, MEM_SIZE);

    printf("Memory content: %s\n", (char*)ptr);

    return 0;

}