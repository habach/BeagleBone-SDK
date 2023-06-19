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

    struct mydata dat1 = {0, 5};
    struct mydata dat2 = {5, 10};

    unsigned long res1;
    unsigned long  res2;

    pthread_create(&p1, NULL, dem, (void*) &dat1);
    pthread_create(&p2, NULL, dem, (void*) &dat2);

    pthread_join(p1, (void*) &res1);
    pthread_join(p2, (void*) &res2);

    unsigned long sum = 0;

    

    // for (int i = 0;i < end; i++) {
    //     if (i % 2) sum += 1;
    // }

    sum = res1 + res2;

    printf("Tong = %lu\n", sum);

    return 0;
}