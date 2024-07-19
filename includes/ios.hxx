#ifndef _IOS_HXX_
#define _IOS_HXX_
#include "types.hxx"
// uint8_t printf(char *str);
#define MAX_WIDTH 80
#define MAX_HEIGHT 24

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
#endif