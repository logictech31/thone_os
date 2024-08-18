#include "../includes/ios.hxx"
#include <typeindex>
namespace std {
    /*
        A BASIC TEMPLATE STACK
        FOR ALL PURPOSE
    */
    template <typename T> Stack<T>::Stack() {
        this->top = -1;
        this->size = 0;
    }
    template <typename T> void Stack<T>::push(T value) {
        this->stack[++this->top] = value;
        this->size++;
    }
    template <typename T> T Stack<T>::pop(void) {
        T ret_val = this->stack[top--];
        this->size--;
        return ret_val;
    }
    template <typename T> u8 Stack<T>::isFull(void) {
        if (top != -1)
            return 1;
        else
            return 0;
    }

    template <typename T> u8 Stack<T>::isEmpty(void) {
        if (top == -1)
            return 1;
        else
            return 0;
    }
    /*
        THE OUTPUT STREAM
    */
    Output_Stream::Output_Stream() {
        VIDEO_MEMORY = (u16 *)0xb8000;
        x = 0;
        y = 0;
    }

    u32 Output_Stream::atoi(char* value) {

    }

    Output_Stream::~Output_Stream() {

    }

    char* Output_Stream::itoa(u32 value) {
        // The Character string tmp will store the value
        char tmp[4096];
        u32 i = 0;
        for(; i < 4096; i++) {
            tmp[i] = (char)0;
        }
        this->operator<<("\nInitialized tmp array");
        // We now push the elements onto a stack. Because we get value % 10 meaning in O T H format (ones, tens, hundreds,...)
        while(0 < value) {
            this->stk.push(value % 10);
            value = value / 10;
        }
        this->operator<<("\nPushed values to stack");
        i = 0;
        // We pop the values from the stack and enter them in the string
        while (stk.isFull()) {
            tmp[i++] = stk.pop() + 48;
        }
        this->operator<<("\nFinal value created");
        return &tmp[0];
    }

    u8 Output_Stream::operator<<(u8 value) {
        char *s = itoa(value);
        this->operator<<(&s[0]);
        return 0;
    }

    u8 Output_Stream::operator<<(char *str) {
        static u16 *VIDEO_MEMORY = (u16*)0xb8000;


        for(int i = 0; str[i] != '\0'; i ++) {
            // Will handle New-line
            switch (str[i]) {
            case '\n':
                x = 0;
                y++;
                break;

            case '\b':
                x--;
                break;

            case '\r':
                y++;
                break;

            default:
                /*  We have done a bitwise operation here to
                    only assign value at lower byte since
                    Higher byte = colour info
                    Lower byte = Actual value
                    This is done to retain the default colour information
                    ---------------------------------------------------------
                    The math behind calculating the VIDEO_MEM[index]'s index is
                    index = MAX_WIDTH_RESOLUTION * current_height + current_width
                    Now why are we doing this?
                    => because, memory is Sequential, no matter which type of array you're using
                    We should be using a 2-dim array as such VIDEO_MEM[x][y], but this is equivalent to
                    VIDEO_MEM[x * y], because... Memory is sequential.
                */
                VIDEO_MEMORY[80*y+x] = (VIDEO_MEMORY[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
            }
            // Goes to newline if x goes out of bounds
            if(x >= 80) {
                y++;
                x = 0;
            }
            // Clears the entire screen if y goes out of bounds
            if(y >= 25) {
                for(y = 0; y < 25; y ++)
                    for(x = 0; x < 25; x ++)
                        VIDEO_MEMORY[80*y+x] = (VIDEO_MEMORY[80*y+x] & 0xFF00) | ' ';
                x = 0;
                y = 0;
            }
        }

            return 0;
        }
}
