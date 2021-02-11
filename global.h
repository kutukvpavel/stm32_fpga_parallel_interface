#pragma once

#include "MyFunctions.h"

#define BUS_PINS A0, A1 //TODO: set real pins here
#define PIN_HIGH_WORD A3
#define PIN_CLOCK A4
#define PIN_RESET A5
#define PIN_READY A6

#define MEMORY_SIZE 4096 //Words x 26 bits wide
#define WORD_LENGTH 26 //bits
#define BYTES_PER_WORD (WORD_LENGTH / 8 + ((WORD_LENGTH % 8 != 0) ? 1 : 0))
#define BUS_WIDTH 13

#define CONTROL_START 'S'
#define CONTROL_HEARTBEAT 'H'

namespace globals {
    extern const uint8_t bus_pins[BUS_WIDTH];
}

namespace my_api {
    void emit_clock_pulse();
    void reset_listener();
    void switch_half_word(bool);
    void read_bus(uint8_t* buffer);
}