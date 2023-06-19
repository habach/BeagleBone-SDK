#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const int SIZE = 4096;
    const char *name = "OS";

    int shm_fd;

    void *ptr;

    char url[256];

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    ftruncate(shm_fd, SIZE);

    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("Enter url: \n");

    scanf("%s", url);

    sprintf(ptr, "%s", url);

    ptr += strlen(url);

    return 0;
}