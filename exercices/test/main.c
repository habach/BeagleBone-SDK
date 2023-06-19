/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: hicl
 *
 * Created on June 3, 2023, 6:52 PM
 */

//#include <stdio.h>
//#include <fcntl.h>
//#include <sys/stat.h>

//int main(int argc, char **argv) {
//    struct stat buf;
//    
//    printf("argc = %d\n",argc);
//    
//    int fd = open(argv[1], O_RDONLY);
//
//    fstat(fd, buf);
//
//
//    if (fd < 0) {
//        printf("Source file not found\n");
//        return fd;
//    }
//    // int rd = opendir(argv[2]);
//    // if (rd < 0) {
//    //     printf("Destination directory not found\n");
//    //     return rd;
//    // }    
//
//    // printf();
//
//    return close(fd); 
//}

#include <stdio.h>
#include <pthread.h>

struct mydata {
    unsigned long start;
    unsigned long end;
};

void *dem(void *dat) {

    unsigned long sum;

    struct mydata *data = (struct mydata *) dat;
    for (int i = data->start; i < data->end; i++) {
        if (i % 2) sum += 1;
    }

    return (void*) sum;

}

int main(int argc, char **argv) {

    pthread_t p1 = 0;
    pthread_t p2 = 0;

    struct mydata dat1 = {0, 5000000000};
    struct mydata dat2 = {500000000, 10000000000};

    unsigned long *res1;
    unsigned long  *res2;

    pthread_create(&p1, NULL, dem, (void*) &dat1);
    pthread_create(&p2, NULL, dem, (void*) &dat2);

    pthread_join(p1, (void*) &res1);
    pthread_join(p2, (void*) &res2);

    unsigned long sum = 0;

    

    // for (int i = 0;i < end; i++) {
    //     if (i % 2) sum += 1;
    // }

    sum = * ((unsigned long *) res1) + *((unsigned long *) res2);

    printf("Tong = %lu\n", sum);

    return 0;
}