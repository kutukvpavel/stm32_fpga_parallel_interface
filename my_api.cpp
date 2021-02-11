#include "global.h"

namespace my_api {

    void emit_clock_pulse()
    {
        digitalWrite(PIN_CLOCK, HIGH);
        digitalWrite(PIN_CLOCK, LOW);
    }

    void reset_listener()
    {
#warning "Check reset signal polarity!"
        digitalWrite(PIN_RESET, HIGH);
        delayMicroseconds(1);
        digitalWrite(PIN_RESET, LOW);
    } 

    void switch_half_word(bool high)
    {
        digitalWrite(PIN_HIGH_WORD, high ? HIGH : LOW);
    }

    void read_bus(uint8_t* buffer)
    {
        for (size_t i = 0; i < BYTES_PER_WORD; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                size_t b = i * 8 + j;
#if ((WORD_LENGTH % 8) != 0)
                if (b >= arraySize(globals::bus_pins)) break;
#endif
                if (digitalRead(globals::bus_pins[i * 8 + j])) buffer[i] |= _BV(j);
            }
        }
    }

}