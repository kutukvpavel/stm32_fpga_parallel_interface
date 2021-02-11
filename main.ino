/* 13-bit wide parallel unidirectional (yet) data bus with external clocking
* HI/LOW half-word control line
* Memory: 4 kWords total, Word = 26 bits
*/

#include "global.h"

namespace globals {
    const uint8_t bus_pins[BUS_WIDTH] = { BUS_PINS };
}

void setup()
{
    for (size_t i = 0; i < arraySize(globals::bus_pins); i++)
    {
        pinMode(globals::bus_pins[i], INPUT);
    }
    pinMode(PIN_READY, INPUT);
    pinMode(PIN_CLOCK, OUTPUT);
    pinMode(PIN_HIGH_WORD, OUTPUT);
    pinMode(PIN_RESET, OUTPUT); //TODO: active-low?

    while (!Serial);
    delay(500);

    Serial.println("Goodnight moon!");
}

void loop()
{
	while (!digitalRead(PIN_READY)) {
        if (Serial) Serial.write(CONTROL_HEARTBEAT);
        delay(1000);
    }
    if (!Serial) {
        while (!Serial);
        delay(500);
    }
    Serial.println();
    
    Serial.write(CONTROL_START);
    uint8_t buffer[BYTES_PER_WORD];
    for (size_t i = 0; i < MEMORY_SIZE; i++)
    {
        my_api::switch_half_word(false);
        my_api::emit_clock_pulse();
        my_api::read_bus(buffer);
        Serial.write(buffer, BYTES_PER_WORD);
        my_api::switch_half_word(true);
        delay(1); //13*8 = 104 bits @ 115200 baud = 0.95mS
        my_api::read_bus(buffer);
        Serial.write(buffer, BYTES_PER_WORD);
        delay(1);
    }
    Serial.println();

    my_api::reset_listener();
}
