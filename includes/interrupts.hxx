#pragma once
#include "types.hxx"
#include "port.hxx"
#include "gdt.hxx"

class Interrupt_Manager {
protected:
    struct Gate_Descriptor {
        uint16_t handle_addr_low_bits; // 2
        uint16_t gdt_cs_selector; // 2
        uint8_t reserved_1; // 1
        uint8_t access_rights; // 1
        uint16_t handle_address_high_bits; // 2
    }__attribute__((packed));
    static Gate_Descriptor Interrupt_Descriptor_Table[256];

    // sets entries in idt
    static void Set_Interrupt_Desc_Table(
        uint8_t interrupt_num, 
        uint16_t gdt_cs_selector_offset,
        void (*handler)(),
        uint8_t Descriptor_Privilege_Level,
        uint8_t Descriptor_Type
        );

public:
    Interrupt_Manager(Global_Descriptor_Table *gdt);
    static uint32_t handle_interrupt(uint8_t interrupt_num, uint32_t esp);
    // timeout interrupt
    static void handle_interrupt_request0x00();
    // keyboard interrupt
    static void handle_interrupt_request0x01();

    ~Interrupt_Manager();
};