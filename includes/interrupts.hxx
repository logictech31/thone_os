#ifndef _INTERRUPTS_HXX_
#define _INTERRUPTS_HXX_
#include "types.hxx"
#include "port.hxx"
#include "gdt.hxx"

class Interrupt_Manager {
protected:
    struct Gate_Descriptor {
        uint16_t handle_addr_low_bits;  // 2 bytes
        uint16_t gdt_cs_selector;       // 2 bytes
        uint8_t reserved;               // 1 byte
        uint8_t access_rights;          // 1 byte
        uint16_t handle_addr_high_bits; // 2 bytes
    }__attribute__((packed)); // Total: 8 bytes
    static Gate_Descriptor Interrupt_Descriptor_Table[256];

    struct Interrupt_Descriptor_Table_Pointer {
        uint16_t size;  // 2 bytes
        uint32_t base;  // 4 bytes
    }__attribute__((packed)); // Total: 6 bytes

    uint16_t hardware_interrupt_offset;
    // sets entries in idt
    static void Set_Interrupt_Descriptor_Table(
        uint8_t interrupt_num,
        uint16_t gdt_cs_selector_offset,
        void (*handler)(),
        uint8_t Descriptor_Privilege_Level,
        uint8_t Descriptor_Type
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

    static uint32_t handle_interrupt(uint8_t interrupt_num, uint32_t esp);
    void Activate();
    void Deactivate();
    static void ignore_interrupt_request();

};
#endif
