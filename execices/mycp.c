#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    struct stat buf;
    
    printf("argc = %d\n",argc);
    
    int fd = open(argv[1], O_RDONLY);

    fstat(fd, &buf);


    if (fd < 0) {
        printf("Source file not found\n");
        return fd;
    }
    // int rd = opendir(argv[2]);
    // if (rd < 0) {
    //     printf("Destination directory not found\n");
    //     return rd;
    // }    

    printf("fd = %d\n", fd);

    return close(fd); 
}