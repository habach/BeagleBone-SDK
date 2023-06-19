#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/timer.h>

struct config
{
    int gpio_num;
    int tan_so;
};

struct config config_data;

#define MAGIC_NO	100
#define SEND_DATA_CMD	_IOW(MAGIC_NO, sizeof(struct config), struct config *)

#define GPIO_20 (20)

static bool first;
static int status;

struct timer_list my_timer;

static void timer_function(struct timer_list *t)
{
    static int count = 0;

    pr_info("delay time is %d\n", config_data.tan_so);

    // Nhap nhay led
    if ((count % config_data.tan_so) == 0)
        gpio_set_value(GPIO_20, 1);
    else
        gpio_set_value(GPIO_20, 0);

    count++;
    mod_timer(t, jiffies + HZ);
}

int misc_open(struct inode *node, struct file *filep)
{
    first = true;
    pr_info("misc_open first is %d\n", first);

    return 0;
}

int misc_release(struct inode *node, struct file *filep)
{
    pr_info("%s, %d\n", __func__, __LINE__);
    first = false;

    return 0;
}

//Doc data tu storage va tra ve cho application
static ssize_t misc_read(struct file *filp, char __user *buf, size_t count,
                         loff_t *f_pos)
{
    int ret = 0;

    pr_info("misc_read first is %d\n", first);

    if (first == false) {
        pr_info("No more data to read\n");
        return 0;
    }

    switch (status)
    {
    case 1:
        ret = copy_to_user(buf, "1", 1);
        break;
    case 0:
        ret = copy_to_user(buf, "0", 1);
        break;
    }
    
    first = false;

    return 1;
}

//Ham write: ghi du lieu vao vung storage
static ssize_t misc_write(struct file *filp, const char __user *buf,
                          size_t count, loff_t *f_pos)
{
    int ret = 0;
    char internal[10];

    if (first == false) {
        pr_info("No more storage to write\n");
        return 0;
    }

    memset(internal, 0, sizeof(internal));
    ret = copy_from_user(internal, buf, 1);

    switch (internal[0])
    {
    case '1':
        gpio_set_value(GPIO_20, 1);
        status = 1;
        //Khoi tao timer
        my_timer.expires = jiffies + config_data.tan_so * HZ;
        timer_setup(&my_timer, timer_function, 0);
        add_timer(&my_timer);
        break;
    case '0':
        gpio_set_value(GPIO_20, 0);
        status = 0;
        del_timer_sync(&my_timer);
        break;
    default:
        pr_info("du lieu khong hop le\n");
        break;
    }
    
    first = false;

    return count;
}

static long misc_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
    int ret = 0;

	switch (cmd) {
	case SEND_DATA_CMD:
		memset(&config_data, 0, (sizeof(struct config)));
		ret = copy_from_user(&config_data, (struct config *)arg, (sizeof(struct config)));
		pr_info("config_data.gpio_num: %d config_data.tanso: %d\n", config_data.gpio_num, config_data.tan_so);
		break;

	default:
		return -ENOTTY;
	}

	return 0;
}

struct file_operations misc_fops = {
    .owner = THIS_MODULE,
    .open = misc_open,
    .release = misc_release,
    .read = misc_read,
    .write = misc_write,
    .unlocked_ioctl = misc_ioctl,
};

static struct miscdevice misc_example = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "misc_example",
    .fops = &misc_fops,
};

static int misc_init(void)
{
    pr_info("misc module init\n");

    if (misc_register(&misc_example) == 0)
    {
        pr_info("registered device file success\n");
    }

    //enable chan pin P9_41 lam gpio output
    if (gpio_is_valid(GPIO_20) == false)
    {
        pr_err("GPIO %d is not valid\n", GPIO_20);
        return -1;
    }

    if(gpio_request(GPIO_20,"GPIO_20") < 0) {
        pr_err("ERROR: GPIO %d request\n", GPIO_20);
        return -1;
    }

    gpio_direction_output(GPIO_20, 0);
    gpio_export(GPIO_20, false);
    status = 0;

    return 0;
}

static void misc_exit(void)
{
    pr_info("misc module exit\n");
    misc_deregister(&misc_example);


}

module_init(misc_init);
module_exit(misc_exit);

MODULE_AUTHOR("Phu Luu An");
MODULE_DESCRIPTION("Example misc driver.");
MODULE_LICENSE("GPL");