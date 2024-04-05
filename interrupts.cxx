#include "includes/interrupts.hxx"
#include "includes/ios.hxx"

Interrupt_Manager::Interrupt_Manager(Global_Descriptor_Table *gdt) {
    uint16_t Code_Segment = gdt->Code_Segment_Select();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    for(uint16_t i = 0; i < 256; i ++)
        Set_Interrupt_Descriptor_Table(i, Code_Segment, &ignore_interrupt_request, 0, IDT_INTERRUPT_GATE);

    Set_Interrupt_Descriptor_Table(0x20, Code_Segment, &ignore_interrupt_request, 0, IDT_INTERRUPT_GATE);
    Set_Interrupt_Descriptor_Table(0x21, Code_Segment, &ignore_interrupt_request, 0, IDT_INTERRUPT_GATE);
}

Interrupt_Manager::~Interrupt_Manager() {

}

uint32_t Interrupt_Manager::handle_interrupt(uint8_t interrupt_num, uint32_t esp) {
    std::cout << "Interrupt!\n";

    return esp;
}

void Interrupt_Manager::handle_interrupt_request0x00() {

}

void Interrupt_Manager::handle_interrupt_request0x01() {

}

/*  Function Name:  ignore_interrupt_request()
    Description:    Ignores every interrupt that we have not set
                    explicitly 
*/
void Interrupt_Manager::ignore_interrupt_request() {

}

void Set_Interrupt_Descriptor_Table(
    uint8_t interrupt_num, 
    uint16_t gdt_cs_selector_offset,
    void (*handler)(),
    uint8_t Descriptor_Privilege_Level,
    uint8_t Descriptor_Type) {
    const uint8_t IDT_DESC_PRESENT = 0x80;
    Interrupt_Descriptor_Table[interrupt_num].handle_addr_low_bits = ((uint32_t)handler) & 0xFFFF;
    Interrupt_Descriptor_Table[interrupt_num].handle_addr_high_bits = (((uint32_t)handler) >> 16) & 0xFFFF;
    Interrupt_Descriptor_Table[interrupt_num].gdt_cs_selector = gdt_cs_selector_offset;
    Interrupt_Descriptor_Table[interrupt_num].reserved = 0;
    Interrupt_Descriptor_Table[interrupt_num].access_rights = IDT_DESC_PRESENT | Descriptor_Type | ((Descriptor_Privilege_Level & 3) << 5);
}