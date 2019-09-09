#include <sleep.hpp>

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/io.h>

void sleep() {
  // enable external interrupt
  GIMSK &= 0b10011111;
  GIMSK |= 0b01000000;

  // sleep
  sei();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
}

ISR(INT0_vect) {
  // disable external interrupt
  GIMSK &= 0b10011111;
  GIMSK |= 0b00000000;

  // disable sleep
  sleep_disable();
}
