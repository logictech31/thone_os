#ifndef _INTERRUPTS_HXX_
#define _INTERRUPTS_HXX_
#include "types.hxx"
#include "port.hxx"
#include "gdt.hxx"

class Interrupt_Manager {
protected:
    struct Gate_Descriptor {
        u16 handle_addr_low_bits;  // 2 bytes
        u16 gdt_cs_selector;       // 2 bytes
        u8 reserved;               // 1 byte
        u8 access_rights;          // 1 byte
        u16 handle_addr_high_bits; // 2 bytes
    }__attribute__((packed)); // Total: 8 bytes
    static Gate_Descriptor Interrupt_Descriptor_Table[256];

    struct Interrupt_Descriptor_Table_Pointer {
        u16 size;  // 2 bytes
        u32 base;  // 4 bytes
    }__attribute__((packed)); // Total: 6 bytes

    u16 hardware_interrupt_offset;
    // sets entries in idt
    static void Set_Interrupt_Descriptor_Table(
        u8 interrupt_num,
        u16 gdt_cs_selector_offset,
        void (*handler)(),
        u8 Descriptor_Privilege_Level,
        u8 Descriptor_Type
    );

    Port_8bit_Slow pic_master_cmd;
    Port_8bit_Slow pic_master_data;
    Port_8bit_Slow pic_worker_cmd;
    Port_8bit_Slow pic_worker_data;

    // timeout interrupt
    static void handle_interrupt_request0x00();
    // keyboard interrupt
    static void handle_interrupt_request0x01();

public:
    Interrupt_Manager(Global_Descriptor_Table *gdt);
    ~Interrupt_Manager();

    static u32 handle_interrupt(u8 interrupt_num, u32 esp);
    void Activate();
    void Deactivate();
    static void ignore_interrupt_request();

};
#endif
