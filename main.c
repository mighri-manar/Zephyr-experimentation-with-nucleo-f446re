#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void main(void)
{
    int ret;

    if (!device_is_ready(led.port)) {
        printk("Error: LED device not ready\n");
        return;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: Failed to configure LED pin\n", ret);
        return;
    }

    printk("LED Blinking with Zephyr on NUCLEO-F446RE!\n");

    while (1) {
        gpio_pin_toggle_dt(&led);
        k_msleep(500);  
    }
}
