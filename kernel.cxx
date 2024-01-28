#include "thone_io.h"

extern "C" void kernel_main(void *multiboot_structure, uint32_t magic_number) {
    printf("Thone_OS started!");
    while(1);
}