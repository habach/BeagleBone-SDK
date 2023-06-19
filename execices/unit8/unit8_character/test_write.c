#include <stdio.h>
#include <string.h>

#define PATH "/dev/misc_example"

int main(int argc, char *argv[])
{
    const char *data = (argv[1]) ? argv[1] : "Test misc device\n";
    
    FILE *fp = fopen(PATH, "w");
    char buf[100];
    int n = 0;

    if (NULL == fp) {
        printf("Mo khong thanh cong\n");
        return -1;
    }

    memset(buf, 0, sizeof(buf));
    memcpy(buf, data, strlen(data));

    printf("Writing: %s", buf);

    n = fwrite(buf, 1, strlen(buf), fp);

    printf("(%d bytes)\n", n);

    fclose(fp);

    return 0;
}