#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/time.h>
// #include <linux/io.h>
#include <linux/delay.h>

int init_module(void)
{
    int i;
	for (i=0; i< 10; i++) {
        pr_info("Driver hello world!\n");
        msleep (1000);
    }

	return 0;
}

void cleanup_module(void)
{
	pr_info("cleaned module");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ha Bach");
MODULE_DESCRIPTION("Hello world kernel module");
