#include <button.hpp>

void setupButton() {
    pinMode(BUTTON_PIN, BUTTON_PRESSED == HIGH ? INPUT : INPUT_PULLUP);
}

bool wasButtonPressedFor(uint16_t millis) {
    uint16_t time_step = 50;

    for (uint16_t passed = 0; passed <= millis; passed += time_step) {
        if (digitalRead(BUTTON_PIN) == HIGH) { // button was unpressed
            return false;
        }
        delay(time_step);
    }

    return true;
}

bool wasButtonUnpressedFor(uint16_t millis) {
    uint16_t time_step = 50;

    for (uint16_t passed = 0; passed <= millis; passed += time_step) {
        if (digitalRead(BUTTON_PIN) == LOW) { // button was pressed
            return false;
        }
        delay(time_step);
    }

    return true;
}

void waitForButtonUnpress() {
    while (digitalRead(BUTTON_PIN) == LOW) { // button is pressed
        delay(50);
    }
}
