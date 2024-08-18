#include "../includes/interrupts.hxx"
#include "../includes/ios.hxx"

Interrupt_Manager::Gate_Descriptor Interrupt_Manager::Interrupt_Descriptor_Table[256];

Interrupt_Manager::Interrupt_Manager(Global_Descriptor_Table *gdt)
:   pic_master_cmd  (0x20),
    pic_master_data (0x21),
    pic_worker_cmd  (0xA0),
    pic_worker_data (0xA1)
{
    i16 Code_Segment = gdt->Code_Segment_Select();

    const u8 IDT_INTERRUPT_GATE = 0x0E;
    u16 i = 0;
    for(; i < 256; i ++)
        Set_Interrupt_Descriptor_Table(i, Code_Segment, &ignore_interrupt_request, 0, IDT_INTERRUPT_GATE);
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
    idt_ptr.base = (i32) this->Interrupt_Descriptor_Table;
    // Loading the interrupt descriptor table
    asm volatile("lidt %0": :"m" (idt_ptr));
}

Interrupt_Manager::~Interrupt_Manager() {

}

void Interrupt_Manager::Activate() {
    asm volatile("sti");
}

u32 Interrupt_Manager::handle_interrupt(u8 interrupt_num, u32 esp) {
    std::cout << "\nInterrupt!";
    std::cout << interrupt_num;

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
    u8 interrupt_num,
    u16 gdt_cs_selector_offset,
    void (*handler)(),
    u8 Descriptor_Privilege_Level,
    u8 Descriptor_Type) {
    const u8 IDT_DESC_PRESENT = 0x80;

    Interrupt_Descriptor_Table[interrupt_num].handle_addr_low_bits = ((u32)handler) & 0xFFFF;
    Interrupt_Descriptor_Table[interrupt_num].handle_addr_high_bits = (((u32)handler) >> 16) & 0xFFFF;
    Interrupt_Descriptor_Table[interrupt_num].gdt_cs_selector = gdt_cs_selector_offset;
    Interrupt_Descriptor_Table[interrupt_num].access_rights = IDT_DESC_PRESENT | Descriptor_Type | ((Descriptor_Privilege_Level & 3) << 5);
    Interrupt_Descriptor_Table[interrupt_num].reserved = 0;

}
