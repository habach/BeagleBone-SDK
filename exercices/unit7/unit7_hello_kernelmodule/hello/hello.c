#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/slab.h>

struct container
{
    char name[25];
    int time;
    int frequence;
    struct timer_list my_timer;
};

// Ham xu ly timer
static void timer_function(struct timer_list *t)
{
    struct container *container_ptr = container_of(t, struct container, my_timer);
    printk(KERN_EMERG "hello world %s\n", container_ptr->name);
}

int init_module(void)
{
    struct container *container1 = NULL;
    struct container *container2 = NULL;

    container1 = kmalloc(sizeof(struct container), GFP_KERNEL);
    container2 = kmalloc(sizeof(struct container), GFP_KERNEL);

    //Setup timer1
    container1->my_timer.expires = jiffies + 3 * HZ;
    container1->my_timer.function = timer_function;
    timer_setup(&(container1->my_timer), timer_function, 0);
    add_timer(&(container1->my_timer));
    memset(container1->name, 0, 25);
    strcpy(container1->name, "Phu");

    //setup timer2
    container2->my_timer.expires = jiffies + 3 * HZ;
    container2->my_timer.function = timer_function;
    timer_setup(&(container2->my_timer), timer_function, 0);
    add_timer(&(container2->my_timer));
    memset(container2->name, 0, 25);
    strcpy(container2->name, "Long");

    return 0;
}

void cleanup_module(void)
{

    pr_info("hello world driver is unloaded\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ta Manh Tuyen");
MODULE_DESCRIPTION("GPIO led kernel module");