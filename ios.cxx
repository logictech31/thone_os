#include "includes/ios.hxx"

// printf definition
uint8_t printf(char* str) {
    static uint16_t *VIDEO_MEMORY = (uint16_t*)0xb8000;
    static uint8_t x = 0, y = 0;

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