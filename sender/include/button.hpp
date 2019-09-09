#include <Arduino.h>

const uint8_t BUTTON_PIN = 2;
const bool BUTTON_PRESSED = LOW;


void setupButton();
bool wasButtonPressedFor(uint16_t millis);
bool wasButtonUnpressedFor(uint16_t millis);
void waitForButtonUnpress();
