#pragma once
#include "types.h"

class Global_Descriptor_Table {
public:
    class Segment_Descriptor {
    private:
        uint16_t limit_lo;
        uint16_t base_lo;
        uint8_t base_hi;
        uint8_t type;
        uint8_t flags_limit_hi;
        uint8_t base_vhi;
    public:
        Segment_Descriptor(uint32_t base, uint32_t limit, uint8_t type);

        uint32_t Base();

        uint32_t Limit();
    } __attribute__((packed));

    Segment_Descriptor Null_Segment_Selector;
    Segment_Descriptor Unused_Segment_Selector;
    Segment_Descriptor Code_Segment_Selector;
    Segment_Descriptor Data_Segment_Selector;

    Global_Descriptor_Table();
    ~Global_Descriptor_Table();

    uint16_t Code_Segment_Select();
    uint16_t Data_Segment_Select();
};