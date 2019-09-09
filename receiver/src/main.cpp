#include <Arduino.h>
#include <IRremote.h>
#include "../../dumb_byte.hpp"

const uint8_t IR_RECEIVE_PIN = PIN0;
const uint8_t TX_SYNC_PIN = PIN1;
const uint8_t TX_DATA_PIN = PIN2;

const uint8_t RECEIVER_ID = 0;

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup() {
    irrecv.enableIRIn();
    pinMode(TX_SYNC_PIN, OUTPUT);
    pinMode(TX_DATA_PIN, OUTPUT);
}

void loop() {
    if (irrecv.decode(&results)) {
        if (results.decode_type == decode_type_t::RC6) {
            uint8_t start    = results.value >> 24;
            uint8_t receiver = results.value >> 16;
            // uint8_t sender = results.value >> 8; // not used atm
            uint8_t message  = results.value;

            if (start == 0b01010101 && receiver == RECEIVER_ID) {
                dumbByteSend(TX_SYNC_PIN, TX_DATA_PIN, message);
            }
        }

        irrecv.resume();
    }
}
