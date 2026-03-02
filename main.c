#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "define.h"

void servo_init(uint gpio)
{
  gpio_set_function(gpio, GPIO_FUNC_PWM);
  fatia_pwm = pwm_gpio_to_slice_num(gpio);

  pwm_config cfg = pwm_get_default_config();
  pwm_config_set_clkdiv(&cfg, CLOCK_DIV);

  pwm_wrap = (CPU_CLOCK / (CLOCK_DIV * PWM_FREQ)) - 1;
  pwm_config_set_wrap(&cfg, pwm_wrap);
  pwm_init(fatia_pwm, &cfg, true);
}

void servo_angulo_pwm(float angle)
{
  if (angle < SERVO_MIN_ANGLE) angle = SERVO_MIN_ANGLE;
  else if (angle > SERVO_MAX_ANGLE) angle = SERVO_MAX_ANGLE;

uint16_t pulso_us = SERVO_MIN_US + (angle / SERVO_MAX_ANGLE)* (SERVO_MAX_US - SERVO_MIN_US);

  uint32_t nivel = (pulso_us * pwm_wrap) / PWM_PERIODO_US;
  pwm_set_gpio_level(PINO_SERVO, nivel);
}


int main() {
  stdio_init_all();
  while (true) {
servo_init(PINO_SERVO);
  for (int i = SERVO_MIN_ANGLE; i <= SERVO_MAX_ANGLE; i++){
    sleep_ms(30);
    servo_angulo_pwm(i);
    
  }
  }
}
