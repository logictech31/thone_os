#include "includes/interrupts.hxx"
#include "includes/ios.hxx"

Interrupt_Manager::Gate_Descriptor Interrupt_Manager::Interrupt_Descriptor_Table[256];

Interrupt_Manager::Interrupt_Manager(Global_Descriptor_Table *gdt)
:   pic_master_cmd  (0x20),
    pic_master_data (0x21),
    pic_worker_cmd  (0xA0),
    pic_worker_data (0xA1)
{

    uint16_t Code_Segment = gdt->Code_Segment_Select();

    const uint8_t IDT_INTERRUPT_GATE = 0x0E;
    uint16_t i = 0;
    for(; i < 256; i ++)
        Set_Interrupt_Descriptor_Table(i, Code_Segment, &ignore_interrupt_request, 0, IDT_INTERRUPT_GATE);
    return;
    Set_Interrupt_Descriptor_Table(0x20, Code_Segment, &handle_interrupt_request0x00, 0, IDT_INTERRUPT_GATE);
    Set_Interrupt_Descriptor_Table(0x21, Code_Segment, &handle_interrupt_request0x01, 0, IDT_INTERRUPT_GATE);

    // Initializing the two PICS
    pic_master_cmd.Write(0x11);
    pic_worker_cmd.Write(0x11);

    pic_master_data.Write(0x20);
    pic_worker_data.Write(0x20);

    pic_master_cmd.Write(0x04);
    pic_worker_cmd.Write(0x02);

    pic_master_cmd.Write(0x01);
    pic_worker_cmd.Write(0x01);

    pic_master_cmd.Write(0x00);
    pic_worker_cmd.Write(0x00);

    Interrupt_Descriptor_Table_Pointer idt_ptr;
    idt_ptr.size = 256 * sizeof(Gate_Descriptor) - 1;
    idt_ptr.base = (uint32_t) gdt;
    // Loading the interrupt descriptor table
    asm volatile("cli");
    asm volatile("lidt %0": :"m" (idt_ptr));
}

Interrupt_Manager::~Interrupt_Manager() {

}

void Interrupt_Manager::Activate() {
    asm("sti");
}

uint32_t Interrupt_Manager::handle_interrupt(uint8_t interrupt_num, uint32_t esp) {
    std::cout << "Interrupt!";

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

void Interrupt_Manager::Set_Interrupt_Descriptor_Table(
    uint8_t interrupt_num,
    uint16_t gdt_cs_selector_offset,
    void (*handler)(),
    uint8_t Descriptor_Privilege_Level,
    uint8_t Descriptor_Type) {
    const uint8_t IDT_DESC_PRESENT = 0x80;
    Interrupt_Descriptor_Table[interrupt_num].handle_addr_low_bits = ((uint32_t)handler) & 0xFFFF;

    Interrupt_Descriptor_Table[interrupt_num].handle_addr_high_bits = (((uint32_t)handler) >> 16) & 0xFFFF;

    Interrupt_Descriptor_Table[interrupt_num].access_rights = IDT_DESC_PRESENT | Descriptor_Type | ((Descriptor_Privilege_Level & 3) << 5);
    Interrupt_Descriptor_Table[interrupt_num].reserved = 0;
    return;
    // Error comes here
    Interrupt_Descriptor_Table[interrupt_num].gdt_cs_selector = gdt_cs_selector_offset;

}
