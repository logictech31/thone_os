#include "includes/ios.hxx"
#include "includes/gdt.hxx"

extern "C" void kernel_main(void *multiboot_structure, uint32_t magic_number) {
    printf("Thone_OS started!\nHello");
    
    Global_Descriptor_Table gdt;
    while(1);
}
