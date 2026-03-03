#define CPU_CLOCK 125000000

//servo motor defines
#define SERVO_MIN_US 500
#define SERVO_MAX_US 2400
#define SERVO_MAX_ANGLE 180.0f
#define SERVO_MIN_ANGLE 0.0f

//pwm defines
#define GPIO_SERVO 28
#define PWM_FREQ 50
#define CLOCK_DIV 125.0f
#define PWM_PERIODO_US 20000 //20ms

// push button pull up p = plus and m = minus
#define push_btn_p 2
float angle = SERVO_MIN_ANGLE;
#define push_btn_m 5

static uint slice_pwm;
static uint32_t pwm_wrap;

/*trying to make a lcd i2c write de angle, but not working at all
MAYBE it works just on arduino, i saw the github/raspberry, but no success

i2c oled sda and scl, default gpo 0, gpo 1, on arduino??
the address is 0x3c/0x3d for i2c https://docs.wokwi.com/parts/board-ssd1306

#define i2cAdress 0x3c  //same of diagram.json
#define I2C_MODULE i2c0 //there are 2 modules of i2c in rasp i2c0, and i2c1 
#define GPIO_SDA 0
#define GPIO_SCL 1
#define DISPLAY_FREQ 400 * 1000
  | -> next line (400hz * 1k = 400khz) 
  | -> https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf 
  | -> page 49, max freq display 407khz


*/
