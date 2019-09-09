#include <Arduino.h>
#include <IRremote.h>
#include <memory.hpp>
#include <button.hpp>
#include <sleep.hpp>

const uint8_t SENDER_ID = 0;
const uint8_t RECEIVER_ID = 0;

const uint8_t INDICATOR_PIN = 0;

uint8_t current_message;

// ir sending is bound to pin 1
// https://github.com/z3t0/Arduino-IRremote#hardware-specifications
IRsend irsend;

uint32_t constructPacket();
void checkAndHandleMessageChange();

void setup() {
    setupButton();
    setupMemory();

    pinMode(INDICATOR_PIN, OUTPUT);
    current_message = readMessage();

    digitalWrite(INDICATOR_PIN, HIGH);
    delay(500);
    digitalWrite(INDICATOR_PIN, LOW);
}

void loop() {
    sleep();

    digitalWrite(INDICATOR_PIN, HIGH);
    irsend.sendRC6(constructPacket(), 32);
    digitalWrite(INDICATOR_PIN, LOW);

    checkAndHandleMessageChange();
}

uint32_t constructPacket() {
    uint32_t packet = 0;

    packet |= uint32_t(0b01010101)  << 24;
    packet |= uint32_t(RECEIVER_ID) << 16;
    packet |= uint32_t(SENDER_ID)   <<  8;
    packet |= uint32_t(current_message);

    return packet;
}

void checkAndHandleMessageChange() {
    if (wasButtonPressedFor(3000)) {

        uint16_t press_count = 0;

        digitalWrite(INDICATOR_PIN, HIGH);
        waitForButtonUnpress();

        // while there are still message options and the button was pressed within 5 seconds
        for (; press_count < 256 && !wasButtonUnpressedFor(5000); press_count++) {
            digitalWrite(INDICATOR_PIN, LOW);
            delay(100);
            digitalWrite(INDICATOR_PIN, HIGH);
            waitForButtonUnpress();
        }

        // if someone selected new message
        if (press_count != 0) {
            current_message = press_count - 1;
            saveMessage(current_message);
        }
    }
    digitalWrite(INDICATOR_PIN, LOW);
    waitForButtonUnpress();
}



