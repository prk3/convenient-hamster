#include <memory.hpp>

void setupMemory() {
  bool initialized = eeprom_read_byte((uint8_t*) 0) == 0;

  if (!initialized) {
    eeprom_write_byte((uint8_t*) 0, 0);
    eeprom_write_byte((uint8_t*) 1, 0);
  }
}

uint8_t readMessage() {
  return eeprom_read_byte((uint8_t*) 1);
}

void saveMessage(uint8_t message) {
  eeprom_write_byte((uint8_t*) 1, message);
}
