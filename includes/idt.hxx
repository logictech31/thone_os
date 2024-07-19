#ifndef _IDT_HXX_
#define _IDT_HXX_
#include "types.hxx"
#include "port.hxx"
#include "gdt.hxx"
/*
    NAME
      Interrupt_Manager
    DESCRIPTION
      Interrupt Descriptor Table
*/
class Interrupt_Manager {
protected:
    struct Gate_Descriptor {
        uint16_t    handler_address_low;
        uint16_t    gdt_cs_selector;
        uint8_t     reserved;
        uint8_t     access_rights;
        uint16_t    handler_address_high;
    } __attribute__((packed));

    struct IDT_Pointer {
        uint16_t size;
        uint32_t base;
    } __attribute__((packed));
    // The Interrupt Vector Table / Interrupt Descriptor Table
    static Gate_Descriptor IVT[256];

    Port_8bit_Slow pic_master_command;
    Port_8bit_Slow pic_master_data;
    Port_8bit_Slow pic_slave_command;
    Port_8bit_Slow pic_slave_data;

    static void Set_Interrupt_Descriptor_Entry(
        uint8_t     interrupt_num,
        uint16_t    cs_selector_offset,
        void        (*handler)(),
        uint8_t     descriptor_privilege_level,
        uint8_t     descriptor_type
    );
public:
    Interrupt_Manager(Global_Descriptor_Table* gdt_p);
    ~Interrupt_Manager();
    static uint32_t handle_interrupt(uint8_t interrupt_num, uint32_t esp);
    static void     handle_interrupt_request0x00(void);
    static void     handle_interrupt_request0x01(void);
    static void     handle_interrupt_exception(void);
    static void     ignore_interrupt_request(void);
    void activate(void);
};
#endif
