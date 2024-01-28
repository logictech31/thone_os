#include "includes/io.h"

void printf(char* str) {
    uint16_t *VIDEO_MEMORY = (uint16_t*)0xb8000;

        for(int i = 0; str[i] != '\0'; i ++)
            VIDEO_MEMORY[i] = (VIDEO_MEMORY[i] & 0xFF00) | str[i];

        return;
}

extern "C" void kernel_main(void *multiboot_structure, uint32_t magic_number) {
    printf("Thone_OS started!");
    while(1);
}
