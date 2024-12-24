#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>
#include <math.h> // For sine function

LOG_MODULE_REGISTER(main);

#define PWM_NODE DT_NODELABEL(pwm2)
#define PWM_CHANNEL 1
#define PWM_PERIOD_USEC 20000 
#define RESOLUTION 1000      


#define PI 3.141592653589793

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

    while (1) {
        
        for (int i = 0; i < 360; i += 10) {
            float sine_value = (sin(i * PI / 180.0) + 1) / 2.0; //normalisation
            pulse_width = sine_value * PWM_PERIOD_USEC;          

            if (pwm_set(pwm_dev, PWM_CHANNEL, PWM_PERIOD_USEC, pulse_width, 0)) {
                LOG_ERR("Failed to set PWM");
            } else {
                LOG_INF("PWM duty cycle set: %d%%", (int)((pulse_width * 100) / PWM_PERIOD_USEC));
            }

            k_sleep(K_MSEC(5)); 
        }
    }
}
