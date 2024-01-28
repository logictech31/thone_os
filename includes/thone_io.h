#pragma once
#include "types.h"
void printf(char *str) {
    uint16_t *VIDEO_MEMORY = (uint16_t*)0xb8000;

    for(int i = 0; str[i] != '\0'; i ++)
        VIDEO_MEMORY[i] = (VIDEO_MEMORY[i] & 0xFF00) | str[i];

    return;
}