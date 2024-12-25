#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main);

#define PWM_NODE DT_NODELABEL(pwm2)
#define PWM_CHANNEL 1
#define INITIAL_FREQ_HZ 500    
#define MAX_FREQ_HZ 2000        
#define MIN_FREQ_HZ 500         
#define DUTY_CYCLE_PERCENT 50   

void main(void)
{
    const struct device *pwm_dev;
    uint32_t freq = INITIAL_FREQ_HZ;
    int step = 50; 
    uint32_t pulse_width, period_usec;

    pwm_dev = DEVICE_DT_GET(PWM_NODE);
    if (!device_is_ready(pwm_dev)) {
        LOG_ERR("PWM device not ready");
        return;
    }

    LOG_INF("PWM device ready");

    while (1) {
        
        period_usec = (1000000U / freq);     // Period = 1/freq in microseconds

        
        pulse_width = (period_usec * DUTY_CYCLE_PERCENT) / 100;

        
        if (pwm_set(pwm_dev, PWM_CHANNEL, period_usec, pulse_width, 0)) {
            LOG_ERR("Failed to set PWM");
        } else {
            LOG_INF("Frequency: %d Hz, Duty Cycle: %d%%", freq, DUTY_CYCLE_PERCENT);
        }

        k_sleep(K_MSEC(100)); 

        
        freq += step;
        if (freq > MAX_FREQ_HZ || freq < MIN_FREQ_HZ) {
            step = -step; 
        }
    }
}
