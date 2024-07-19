#include "includes/ios.hxx"
#include "includes/gdt.hxx"
#include "includes/idt.hxx"

extern "C" void kernel_main(void *multiboot_structure, uint32_t magic_number) {
    std::cout << "\nWelcome!\nThone_OS started!\nroot@localhost > ";
    
    Global_Descriptor_Table gdt;
    Interrupt_Manager idm(&gdt);

    idm.activate();
    
    while(1);
}
