#pragma once
#include "../includes/types.hxx"
// uint8_t printf(char *str);

namespace std {
    class Output_Stream {
    protected:
        uint16_t *VIDEO_MEMORY;
        uint8_t x, y;

        enum vga_color {
            BLACK,
            BLUE,
            GREEN,
            CYAN,
            RED,
            MAGENTA,
            BROWN,
            GREY,
            DARK_GREY,
            BRIGHT_BLUE,
            BRIGHT_GREEN,
            BRIGHT_CYAN,
            BRIGHT_RED,
            BRIGHT_MAGENTA,
            YELLOW,
            WHITE,
        };

        char* itoa(char * str);
    public:
        Output_Stream();
        ~Output_Stream();
        uint8_t operator<<(char *str);
    };

    static Output_Stream cout;
}
