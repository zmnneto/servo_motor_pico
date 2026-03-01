#define CPU_CLOCK 125000000

//#defines para o servomotor

#define SERVO_MIN_US 500
#define SERVO_MAX_US 2400
#define SERVO_MAX_ANGLE 180.0f
#define SERVO_MIN_ANGLE 0.0f

//defines para o pwm
#define PINO_SERVO 28
#define PWM_FREQ 50
#define CLOCK_DIV 125.0f
#define PWM_PERIODO_US 20000 //20ms

static uint fatia_pwm;
static uint32_t pwm_wrap;
