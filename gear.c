#include <bcm2835.h>
#include <stdio.h>

// Blinks on RPi pin GPIO 11
#define OUT1_1 RPI_GPIO_P1_11
#define OUT1_2 RPI_GPIO_P1_15
#define OUT2_1 RPI_GPIO_P1_16
#define OUT2_2 RPI_GPIO_P1_18
#define PWM1 RPI_GPIO_P1_12
#define PWM2 RPI_GPIO_P1_12
#define PWM1_CHANNEL 0
#define PWM2_CHANNEL 0
#define RANGE 1000
#define MIN_DATA 500
#define MAX_DATA 1000

void move_front() {
  bcm2835_gpio_write(OUT1_1, HIGH);
  bcm2835_gpio_write(OUT1_2, LOW);
  bcm2835_gpio_write(OUT2_1, HIGH);
  bcm2835_gpio_write(OUT2_2, LOW);
}

void move_back() {
  bcm2835_gpio_write(OUT1_1, LOW);
  bcm2835_gpio_write(OUT1_2, HIGH);
  bcm2835_gpio_write(OUT2_1, LOW);
  bcm2835_gpio_write(OUT2_2, HIGH);
}

void stop() {

  bcm2835_gpio_write(OUT1_1, LOW);
  bcm2835_gpio_write(OUT1_2, LOW);
  bcm2835_gpio_write(OUT2_1, LOW);
  bcm2835_gpio_write(OUT2_2, LOW);
}

void turn_right() {
  bcm2835_gpio_write(OUT1_1, LOW);
  bcm2835_gpio_write(OUT1_2, HIGH);
  bcm2835_gpio_write(OUT2_1, HIGH);
  bcm2835_gpio_write(OUT2_2, LOW);
}

void turn_left() {
  bcm2835_gpio_write(OUT1_1, HIGH);
  bcm2835_gpio_write(OUT1_2, LOW);
  bcm2835_gpio_write(OUT2_1, LOW);
  bcm2835_gpio_write(OUT2_2, HIGH);
}

int main(int argc, char **argv)
{
  // If you call this, it will not actually access the GPIO
  // Use for testing
  //bcm2835_set_debug(1);

  if (!bcm2835_init())
    return 1;

  // Set the pin to be an output
  bcm2835_gpio_fsel(OUT1_1, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(OUT1_2, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(OUT2_1, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(OUT2_2, BCM2835_GPIO_FSEL_OUTP);
  //bcm2835_gpio_fsel(PWM1, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(PWM1, BCM2835_GPIO_FSEL_ALT5);

  bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
  bcm2835_pwm_set_mode(PWM1_CHANNEL, 1, 1);
  bcm2835_pwm_set_range(PWM1_CHANNEL, RANGE);

  int direction = 1;
  int data = MAX_DATA - 1;

  bcm2835_pwm_set_data(PWM1_CHANNEL, 999);

  bcm2835_gpio_write(OUT1_1, LOW);
  bcm2835_gpio_write(OUT1_2, LOW);
  bcm2835_gpio_write(OUT2_1, LOW);
  bcm2835_gpio_write(OUT2_2, LOW);

  while (1) {
    char key;
    printf("Next key: ");
    scanf(" %c", &key);
    printf("The key is: %c\n", key);

    switch(key) {
      case 'd':
        turn_right();
        break;
      case 'a':
        turn_left();
        break;
      case 's':
        move_back();
        break;
      case 'w':
        move_front();
        break;
      default:
        stop();
        break;
    }
  }

  return 0;
}

/**
  ** PWM **
  while (1) {
    printf("data=%d\ndirection=%d\n", data, direction);
    if (data == MIN_DATA)
      direction = 1;   // Switch to increasing
    else if (data == MAX_DATA - 1)
      direction = -1;  // Switch to decreasing
    data += direction;
    bcm2835_pwm_set_data(PWM1_CHANNEL, data);
    bcm2835_delay(5);
  }

**/
