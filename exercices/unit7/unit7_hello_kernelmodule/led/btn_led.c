/*******************************************************************************
* Copyright (c) 2015 Song Yang @ ittraining
*
* All rights reserved.
* This program is free to use, but the ban on selling behavior.
* Modify the program must keep all the original text description.
*
* Email: onionys@ittraining.com.tw
* Blog : http://blog.ittraining.com.tw
*******************************************************************************/


#include <linux/module.h>   
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>


#define LED 31
#define LED2 20
#define BUTTON 72
#define MY_GPIO_INT_NAME "my_button_int"
#define MY_DEV_NAME "my_device"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("habach");
MODULE_DESCRIPTION("A GPIO Device Driver module for Beaglebone Green");

static short int button_irq = 0;
static unsigned long flags = 0;
static int led_trigger = 0;

static irqreturn_t button_isr(int irq, void *data)
{
	local_irq_save(flags);
	pr_info("button isr !!!!\n");
	gpio_set_value(LED, led_trigger);
	led_trigger = led_trigger ? (0):(1);
	local_irq_restore(flags);
	return IRQ_HANDLED;
}

int init_led(int led, int init_value, const char *name) {
	if (! name) name = "LED";
	if(gpio_is_valid(led) < 0) {
		pr_err("GPIO #%d is INVALID!\n", led);
		return -1;
	}
	pr_info("GPIO %d assigned to %s.\n", led, name);
	if (gpio_request(led, name) < 0) {
		pr_err("GPIO %d for %s is unavailable!\n", led, name);
		return -1;
	}
	pr_info("GPIO %d for %s is ready.\n", led, name);
	gpio_direction_output(led, 0 );
	gpio_set_value(led, init_value);
	return 0;
}

int init_button(int button, const char *name) {

	if (! name) name = "BUTTON";
	if(gpio_request(button, name) < 0) {
		pr_err("GPIO %d for %s is ready.\n", button, name);
		return -1;
	}
	pr_info("GPIO #%d assigned to %s is ready.\n", button, name);
	if(gpio_is_valid(button) < 0) {
		pr_info("GPIO  %d for %s is invalid!\n", button, name);
		return -1;
	}
	if( (button_irq = gpio_to_irq(button)) < 0 )  {
		pr_err("Setting IRQ for GPIO %d for %s failed!\n", button, name);
		return -1;
	}
	pr_info("IRQ for GPIO %d for %s has been set.\n", button, name);
	if( request_irq( button_irq, button_isr ,IRQF_TRIGGER_FALLING, MY_GPIO_INT_NAME, MY_DEV_NAME)) {
		pr_info("IRQ for GPIO %d (%s) is not available!\n", button, name);
		return -1;
	}
	pr_info("IRQ for GPIO %d (%s) is ready.\n", button, name);
	return 0;
}


int init_module(void)
{
	// -- setup the led gpio as output
	pr_info("module: button interrupt example.\n");
	init_led(LED, 1, "LED 1");
	init_led(LED2, 1, "LED 2");
	init_button(BUTTON, "Button 1");

	// -- setup the button gpio as input and request irq
	
	return 0;

}


void cleanup_module(void)
{
	gpio_set_value(LED, 0);
	gpio_set_value(LED2, 0);
	gpio_free(LED);
	gpio_free(LED2);
	free_irq(button_irq, MY_DEV_NAME);
	gpio_free(BUTTON);
}