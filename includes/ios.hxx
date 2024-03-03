#pragma once
#include "types.hxx"
// uint8_t printf(char *str);

namespace std {
    class Output_Stream {
    protected:
        uint16_t *VIDEO_MEMORY;
        uint8_t x, y;
    public:
        Output_Stream();
        ~Output_Stream();
        uint8_t operator<<(char *str);
    };

    static Output_Stream cout;
}