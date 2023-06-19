/*---------------LINUX KERNEL MODULE EXAMPLE ---------------
Blinking multiple LEDs with timer technique
Author: habach (habach.dev@gmail.com)
Date: Jun 18, 2023
Board: BeagleBone Green V1
Kernel version: 5.4.242-bone66
----------------------------------------------------------*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/slab.h>
#include <linux/gpio.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ha Bach");
MODULE_DESCRIPTION("LED control with timer");

#define LEDS 2 //number of LEDs
#define GREEN_LED 200 //GPIO pin for green LED
#define BLUE_LED 31 //GPIO pin for blue LED
#define GREEN_CYCLE 2 //blinking cycle in seconds for green LED
#define BLUE_CYCLE 4 //blinking cycle in seconds for blue LED

typedef struct _led_t {
    char *name; 
    int pin; //GPIO pin assigned to LED
    int cycle; //LED's blinking cycle in seconds
    int state_buf; //Buffer for storing LED state
    int ready; // Flag to indicate that LED is ready
} led_t;

static led_t leds[LEDS];
static struct timer_list my_timer;
static unsigned long ticks = 0;

static int init_led(led_t *led, int pin, int cycle, int init_state, char *led_name) {

	led->name = (led_name) ? led_name : "LED";
    led->pin = pin;
    led->cycle = cycle;    
    
	if(gpio_is_valid(led->pin) < 0) {
		pr_err("GPIO #%d is INVALID!\n", led->pin);
		return -1;
	}	

	if (gpio_request(led->pin, led->name) < 0) {
		pr_err("GPIO %d for %s is unavailable!\n", led->pin, led->name);
		return -1;
	}

	pr_info("GPIO %d assigned to %s LED.\n", led->pin, led->name);
    pr_info ("%s LED is ready.\n", led->name);

	gpio_direction_output(led->pin, 0 );
	gpio_set_value(led->pin, init_state);
    led->state_buf = init_state;
    led->ready = 1;
    
	return 0;
}

// Timer interrupt callback
static void timer_function(struct timer_list *t)
{
    int i;

    pr_info("Counts: %lu...", ticks);

    for (i=0; i<LEDS; i++) {  
        if (leds[i].ready && !(ticks % leds[i].cycle)) {
            leds[i].state_buf = (leds[i].state_buf) ? 0 : 1;
            gpio_set_value(leds[i].pin, leds[i].state_buf);
            pr_info("Toggled %s.\n", leds[i].name);
        } else if (!leds[i].ready) {
            pr_warn ("LED %s at GPIO %d not ready!\n", leds[i].name, leds[i].pin);
        }
    }

    ticks++;
    mod_timer(t, jiffies + 1*HZ);
}

int init_module(void) {
    
    //Setup LEDs
    init_led(&(leds[0]), GREEN_LED, GREEN_CYCLE, 0, "GREEN");
    init_led(&(leds[1]), BLUE_LED, BLUE_CYCLE, 0, "BLUE");

    //Setup timer
    timer_setup(&my_timer, timer_function, 0);
    mod_timer(&my_timer, jiffies + 1*HZ); //1 Hz ticking

    pr_info("Module loaded.\n");
    return 0;
}

void cleanup_module(void) {
    gpio_set_value(GREEN_LED, 0);
    gpio_set_value(BLUE_LED, 0);
    gpio_free(GREEN_LED);
    gpio_free(BLUE_LED);
    del_timer(&my_timer);
    pr_info("Module unloaded.\n");
}