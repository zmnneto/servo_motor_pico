//https://github.com/raspberrypi/pico-examples/blob/master/i2c/ssd1306_i2c/ssd1306_i2c.c#L104
//https://github.com/raspberrypi/pico-examples/blob/master/i2c/ssd1306_i2c/ssd1306_i2c.c#L104

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"

#include "define.h"

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

void control_servo_wButtons(){
      if(!gpio_get(push_btn_p))
    {
        angle += 10;
      
          if(angle > SERVO_MAX_ANGLE)
          {
              angle = SERVO_MIN_ANGLE;
          } 
          servo_angle_pwm(angle);
          sleep_ms(300);  
    }
    else if(!gpio_get(push_btn_m)){
      angle -= 10;
        if(angle < SERVO_MIN_ANGLE){
          angle = SERVO_MIN_ANGLE;
        }
        servo_angle_pwm(angle);
        sleep_ms(300);
    }
}

int main() {
  stdio_init_all();

  servo_init(GPIO_SERVO);

  gpio_init(push_btn_p);
  gpio_set_dir(push_btn_p, GPIO_IN);
  gpio_pull_up(push_btn_p);
  
  gpio_init(push_btn_m);
  gpio_set_dir(push_btn_m, GPIO_IN);
  gpio_pull_up(push_btn_m);
  
  servo_angle_pwm(angle);
  
  while(true){
      control_servo_wButtons();
  }

  return 0;
}
