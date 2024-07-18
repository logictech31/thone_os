#include "includes/descriptors.hxx"
#include "includes/ios.hxx"
using namespace descriptors;

Interrupt_Manager::Interrupt_Manager(Global_Descriptor_Table *gdt_p) 
: pic_master_command(0x20),
pic_master_data(0x21),
pic_slave_command(0xA0),
pic_slave_data(0xA1)
{
    uint16_t CodeSegment = gdt_p->Code_Segment_Select();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    pic_master_command.Write(0x11);
    pic_slave_command.Write(0x11);

    pic_master_data.Write(0x20);
    pic_slave_data.Write(0x28);
    pic_master_data.Write(0x04);
    pic_slave_data.Write(0x02);
    pic_master_data.Write(0x01);
    pic_slave_data.Write(0x01);
    pic_master_data.Write(0x00);
    pic_slave_data.Write(0x00);

    // Makes entries in the Interrupt Vector Table / Interrupt Descriptor Table
    for ( uint16_t i = 0; i < 256; i ++ ) {
        Interrupt_Manager::Set_Interrupt_Descriptor_Entry(i, CodeSegment, &(this->ignore_interrupt_request), 0, IDT_INTERRUPT_GATE);
    }

    Interrupt_Manager::Set_Interrupt_Descriptor_Entry(0x20, CodeSegment, &(this->handle_interrupt_request0x00), 0, IDT_INTERRUPT_GATE);
    Interrupt_Manager::Set_Interrupt_Descriptor_Entry(0x21, CodeSegment, &(this->handle_interrupt_request0x01), 0, IDT_INTERRUPT_GATE);

    IDT_Pointer idt;
    idt.size = 256 * sizeof(Gate_Descriptor) - 1;
    idt.base = (uint32_t) Interrupt_Vector_Table;

    asm volatile("lidt %0": :"m" (idt));
}

uint32_t Interrupt_Manager::handle_interrupt(uint8_t interrupt_num, uint32_t esp) {
    std::cout << " INTERRUPT";
    return esp;
}

void Interrupt_Manager::handle_interrupt_request0x00(void) {

}

void Interrupt_Manager::handle_interrupt_request0x01(void) {

}

void Interrupt_Manager::Set_Interrupt_Descriptor_Entry(
            uint8_t     interrupt_num,
            uint16_t    cs_selector_offset,
            void        (*handler)(),
            uint8_t     descriptor_privilege_level,
            uint8_t     descriptor_type
) {
    const uint8_t IDT_DESC_PRESENT = 0x80;

    Interrupt_Manager::Interrupt_Vector_Table[interrupt_num].handler_address_high = ((uint32_t)handler >> 16) & 0xFFF;
    Interrupt_Manager::Interrupt_Vector_Table[interrupt_num].handler_address_low = ((uint32_t)handler) & 0xFFF;
    Interrupt_Manager::Interrupt_Vector_Table[interrupt_num].access_rights = IDT_DESC_PRESENT | ((descriptor_privilege_level & 3) << 5) | descriptor_type;
    Interrupt_Manager::Interrupt_Vector_Table[interrupt_num].gdt_cs_selector = cs_selector_offset;
    Interrupt_Manager::Interrupt_Vector_Table[interrupt_num].reserved = 0;
}


void Interrupt_Manager::activate(void) {
    asm("sti");
}