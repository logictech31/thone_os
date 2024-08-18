#include "../includes/port.hxx"

Port::Port(uint16_t port_num) {
    this->port_num = port_num;
}
Port::~Port() {

}
// ---------------------------------------------- //
// Configuring 8bit port here
Port_8bit::Port_8bit(uint16_t port_num):Port(port_num) {

}
Port_8bit::~Port_8bit() {

}
void Port_8bit::Write(uint8_t data) {
    __asm__ volatile("outb %0, %1": :"a"(data), "Nd" (port_num));
}

uint8_t Port_8bit::Read() {
    uint8_t result;
    __asm__ volatile("inb %1, %0": "=a" (result): "Nd" (port_num));
    return result;
}
// ---------------------------------------------- //
// Configuring 8bit slow port here
Port_8bit_Slow::Port_8bit_Slow(uint16_t port_num):Port_8bit(port_num) {

}
Port_8bit_Slow::~Port_8bit_Slow() {

}
void Port_8bit_Slow::Write(uint8_t data) {
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:": :"a"(data), "Nd" (port_num));
}
// ---------------------------------------------- //
// Configuring 16bit port here
Port_16bit::Port_16bit(uint16_t port_num):Port(port_num) {

}
Port_16bit::~Port_16bit() {

}
void Port_16bit::Write(uint16_t data) {
    __asm__ volatile("outw %0, %1": :"a"(data), "Nd" (port_num));
}

uint16_t Port_16bit::Read() {
    uint16_t result;
    __asm__ volatile("inw %1, %0": "=a" (result): "Nd" (port_num));
    return result;
}
// ---------------------------------------------- //
// Configuring 32bit port here
Port_32bit::Port_32bit(uint32_t port_num):Port(port_num) {

}
Port_32bit::~Port_32bit() {

}
void Port_32bit::Write(uint32_t data) {
    __asm__ volatile("outl %0, %1": :"a"(data), "Nd" (port_num));
}

uint32_t Port_32bit::Read() {
    uint32_t result;
    __asm__ volatile("inl %1, %0": "=a" (result): "Nd" (port_num));
    return result;
}
// ---------------------------------------------- //
