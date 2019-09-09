#include <avr/eeprom.h>

void setupMemory();
uint8_t readMessage();
void saveMessage(uint8_t message);
