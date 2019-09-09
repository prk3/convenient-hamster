#include <Arduino.h>
#include <DigiKeyboard.h>
#include "../../dumb_byte.hpp"

const uint8_t INDICATOR_PIN = PIN0;
const uint8_t RX_SYNC_PIN = PIN1;
const uint8_t RX_DATA_PIN = PIN2;

void setup() {
    pinMode(INDICATOR_PIN, OUTPUT);
    pinMode(RX_SYNC_PIN, INPUT);
    pinMode(RX_DATA_PIN, INPUT);

    digitalWrite(INDICATOR_PIN, HIGH);
    delay(500);
    digitalWrite(INDICATOR_PIN, LOW);
}

void loop() {
    int16_t byte = dumbByteReceive(RX_SYNC_PIN, RX_DATA_PIN);

    if (byte >= 0) {
        digitalWrite(INDICATOR_PIN, HIGH);

        switch (byte) {
            case 0:
                DigiKeyboard.sendKeyStroke(KEY_D, MOD_CONTROL_LEFT);
                break;
            /* add more actions here. here are some examples:
            case 1:
                DigiKeyboard.print("Print this");
                break;
            case 2:
                DigiKeyboard.println("Print this and start a new line");
                break;
            case 3:
                // open a terminal on linux and print git status
                DigiKeyboard.sendKeyStroke(KEY_T, MOD_CONTROL_LEFT | MOD_ALT_LEFT);
                DigiKeyboard.delay(500);
                DigiKeyboard.println("git status");
                break;
            case 4:
            default:
                // run something on windows
                DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
                DigiKeyboard.delay(500);
                DigiKeyboard.println("regedit");
                break;
            */
        }

        DigiKeyboard.delay(20);
        digitalWrite(INDICATOR_PIN, LOW);
    }

    DigiKeyboard.update();
}
