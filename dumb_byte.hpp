// this is a very dumb message sending mechanism. please don't use it, except
// if you can't use interrupts. whenever sync pin is pulled high, a data pin
// is set to the next bit in byte parameter. send function padds transmission
// with 1 milisecond of both pins being low. receive function starts listening
// when sync is high and has a timeout of 18ms. negative return value
// indicates an unsuccessful read.
#pragma once
#include <Arduino.h>

void dumbByteSend(uint8_t sync_pin, uint8_t data_pin, uint8_t byte) {
    digitalWrite(sync_pin, LOW);
    digitalWrite(data_pin, LOW);
    delayMicroseconds(1000);

    for (uint8_t mask = 1 << 7; mask != 0; mask >>= 1) {
        digitalWrite(data_pin, byte & mask ? HIGH : LOW);
        digitalWrite(sync_pin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(sync_pin, LOW);
        delayMicroseconds(1000);
    }

    digitalWrite(sync_pin, LOW);
    digitalWrite(data_pin, LOW);
    delayMicroseconds(1000);
}

int16_t dumbByteReceive(uint8_t sync_pin, uint8_t data_pin) {
    uint8_t byte = 0;
    uint8_t mask = 1 << 7;

    unsigned long start_micros = micros();
    unsigned long end_micros = start_micros + 18000; // a transmission should take < 18 ms

    auto should_fail = [&]() {
        unsigned long now = micros();

        // overflow
        if (end_micros < start_micros) {
            return now >= end_micros && now <= start_micros;
        }

        return !(now >= start_micros && now <= end_micros);
    };

    if (digitalRead(sync_pin) == LOW) {
        return -1;
    }

    int iter = 0;

    while (true) {
        byte |= mask & (digitalRead(data_pin) == HIGH ? 255 : 0);
        mask >>= 1;

        if (mask == 0) break;

        // wait for low
        while (digitalRead(sync_pin) == HIGH) {
            if (should_fail()) {
                return -(iter * 10 + 2);
            }
        }

        // wait for high
        while (digitalRead(sync_pin) == LOW) {
            if (should_fail()) {
                return -(iter * 10 + 3);
            }
        }
        iter++;
    }

    return byte;
}
