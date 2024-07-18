#include "includes/ios.hxx"
#include "includes/descriptors.hxx"

extern "C" void kernel_main(void *multiboot_structure, uint32_t magic_number) {
    std::cout << "\nWelcome!\nThone_OS started!\nroot@localhost > ";
    
    descriptors::Global_Descriptor_Table gdt;
    descriptors::Interrupt_Manager idm(&gdt);

    idm.activate();
    
    while(1);
}
