#pragma once
#include "../includes/types.hxx"
// uint8_t printf(char *str);

namespace std {
    template <typename T> class Stack;
    template <typename T>
    class Stack {
    private:
        u32 top;
        u32 size;
        T stack[4096];
    public:
        Stack();
        void push(T value);
        u8 isFull(void);
        u8 isEmpty(void);
        T pop(void);
    };

    class Output_Stream {
    protected:
        u16 *VIDEO_MEMORY;
        u8 x, y;
        Stack<u8> stk;
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

        char* itoa(u32 value);
        u32 atoi(char* value);
    public:
        Output_Stream();
        ~Output_Stream();
        u8 operator<<(char *str);
        u8 operator<<(u8 value);
    };

    static Output_Stream cout;
}
