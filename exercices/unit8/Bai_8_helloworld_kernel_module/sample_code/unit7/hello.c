#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void)
{
    pr_info("hello world driver is loaded\n");

    return 0;
}

void cleanup_module(void)
{
    pr_info("hello world driver is unloaded\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ta Manh Tuyen");
MODULE_DESCRIPTION("GPIO led kernel module");