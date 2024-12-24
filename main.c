#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main);

#define PWM_NODE DT_NODELABEL(pwm2) 
#define PWM_CHANNEL 1             
#define PWM_PERIOD_USEC 20000      

void main(void)
{
    const struct device *pwm_dev;
    uint32_t pulse_width;

   
    pwm_dev = DEVICE_DT_GET(PWM_NODE);
    if (!device_is_ready(pwm_dev)) {
        LOG_ERR("PWM device not ready");
        return;
    }

    LOG_INF("PWM device ready");

        pulse_width = PWM_PERIOD_USEC / 2;

    while (1) {
        
        if (pwm_set(pwm_dev, PWM_CHANNEL, PWM_PERIOD_USEC, pulse_width, 0)) {
            LOG_ERR("Failed to set PWM");
        } else {
            LOG_INF("PWM signal set to 50%% duty cycle");
        }

        k_sleep(K_MSEC(1000)); 
    }
}
