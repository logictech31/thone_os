#include "../includes/ios.hxx"
#include "../includes/gdt.hxx"
#include "../includes/interrupts.hxx"

extern "C" void kernel_main(void *multiboot_structure, u32 magic_number) {
    std::cout << "\nThone_OS started!";
    Global_Descriptor_Table gdt;
    Interrupt_Manager idt(&gdt);
    std::cout << "\nActivating IDT"
    idt.Activate();
    while(1);
}
