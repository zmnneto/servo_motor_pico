#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "define.h"

//kkkkk vi um nerdola fazendo em .go, find about it!
void i2c_init_display(){
  i2c_init(I2C_MODULE, DISPLAY_FREQ);
  gpio_set_function(,GPIO_SET_I2C)
}
void servo_init(uint gpio)
{
  gpio_set_function(gpio, GPIO_FUNC_PWM);
  slice_pwm = pwm_gpio_to_slice_num(gpio);

  pwm_config cfg = pwm_get_default_config();
  pwm_config_set_clkdiv(&cfg, CLOCK_DIV);

  pwm_wrap = (CPU_CLOCK / (CLOCK_DIV * PWM_FREQ)) - 1;
  pwm_config_set_wrap(&cfg, pwm_wrap);
  pwm_init(slice_pwm, &cfg, true);
}

void servo_angle_pwm(float angle)
{
  if (angle < SERVO_MIN_ANGLE) angle = SERVO_MIN_ANGLE;
  if (angle > SERVO_MAX_ANGLE) angle = SERVO_MAX_ANGLE;

  uint16_t pulso_us = SERVO_MIN_US + (angle / SERVO_MAX_ANGLE)* (SERVO_MAX_US - SERVO_MIN_US);

  uint32_t nivel = (pulso_us * pwm_wrap) / PWM_PERIODO_US;
  
  pwm_set_gpio_level(GPIO_SERVO , nivel);
  
}


int main() {
  stdio_init_all();

  servo_init(GPIO_SERVO);
  
  gpio_init(push_btn);
  gpio_set_dir(push_btn, GPIO_IN);
  gpio_pull_up(push_btn);

  servo_angle_pwm(angle);
  
  while(true){

    if(!gpio_get(push_btn))
    {
        angle += 10;
          if(angle > SERVO_MAX_ANGLE) angle = SERVO_MIN_ANGLE;
            servo_angle_pwm(angle);
            sleep_ms(300);  
              
    }
  }

  return 0;
}
