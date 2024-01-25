void printf(char *str) {
    unsigned short *VIDEO_MEMORY = (unsigned short*)0xb8000;

    for(int i = 0; str[i] != '\0'; i ++)
        VIDEO_MEMORY[i] = (VIDEO_MEMORY[i] & 0xFF00) | str[i];

    return;
}