#include "../includes/gdt.hxx"
/*
    Here the Code segment will start at index 0 and 64MB
*/

Global_Descriptor_Table::Global_Descriptor_Table()
: Null_Segment_Selector(0, 0, 0),
Unused_Segment_Selector(0, 0, 0),
Code_Segment_Selector(0, 64 * 1024 * 1024, 0x9A),
Data_Segment_Selector(0, 64 * 1024 * 1024, 0x92) {
    // The processor expects 6 bytes in a row
    u32 i[2];
    // This has the address of the table itself
    i[1] = (u32) this;
    // We right shift by 16 because it is supposed to be the high bytes
    i[0] = sizeof(Global_Descriptor_Table) << 16;

    // We now tell the assembler to use this table that we've declared
    asm volatile("lgdt (%0)": :"p" (((u8 *)i)+2));
}

Global_Descriptor_Table::~Global_Descriptor_Table() {

}

u16 Global_Descriptor_Table::Data_Segment_Select() {
    return (u8 *) &Data_Segment_Selector - (u8 *) this;
}

u16 Global_Descriptor_Table::Code_Segment_Select() {

    return (u16)((u8 *) &Code_Segment_Selector - (u8 *) this);

}

Global_Descriptor_Table::Segment_Descriptor::Segment_Descriptor (u32 base, u32 limit, u8 flags) {
    u8* target = (u8*) this;

    // we have to do this because the gdt structure is very spread out
    if(limit <= 65536) {
        // we set the 6th byte to 0x40 hex value which tells the processor that this is a 16-bit entry
        target[6] = 0x40;
    } else {
        // 0xFFF = 4095
        if((limit & 0xFFF) != 0xFFF){
            limit = (limit >> 12) - 1;
        } else{
            limit = limit >> 12;
        }
        target[6] = 0xC0;
    }

    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF;

    // Now we encode the pointer
    target[2] = base & 0xFF;
    target[3] = (base >> 0x8) & 0xFF;
    target[4] = (base >> 0x10) & 0xFF;
    target[7] = (base >> 0x18) & 0xFF;

    target[5] = flags;
}

u32 Global_Descriptor_Table::Segment_Descriptor::Base() {
    u8 *target = (u8*) this;
    u32 result = target[7];

    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];

    return result;
}

u32 Global_Descriptor_Table::Segment_Descriptor::Limit() {
    u8* target = (u8 *) this;
    u32 result = target[6] & 0xF;
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];
    if((target[6] & 0xC0) == 0xC0)
        result = (result << 12) | 0xFFF;

    return result;
}
