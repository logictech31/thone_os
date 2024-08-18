#ifndef _GDT_HXX_
#define _GDT_HXX_
#include "types.hxx"

class Global_Descriptor_Table {
public:
    class Segment_Descriptor {
    private:
        u16 limit_lo;  // 2
        u16 base_lo;   // 2
        u8 base_hi;    // 1
        u8 type;       // 1
        u8 flags_limit_hi; // 1
        u8 base_vhi;       // 1
        // Total: 8 bytes
    public:
        Segment_Descriptor(u32 base, u32 limit, u8 flags);

        u32 Base();

        u32 Limit();
    } __attribute__((packed));

    Segment_Descriptor Null_Segment_Selector;
    Segment_Descriptor Unused_Segment_Selector;
    Segment_Descriptor Code_Segment_Selector;
    Segment_Descriptor Data_Segment_Selector;

    Global_Descriptor_Table();
    ~Global_Descriptor_Table();

    u16 Code_Segment_Select();
    u16 Data_Segment_Select();
};
#endif
