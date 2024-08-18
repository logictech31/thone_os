#include "../includes/port.hxx"

Port::Port(u16 port_num) {
    this->port_num = port_num;
}
Port::~Port() {

}
// ---------------------------------------------- //
// Configuring 8bit port here
Port_8bit::Port_8bit(u16 port_num):Port(port_num) {

}
Port_8bit::~Port_8bit() {

}
void Port_8bit::Write(u8 data) {
    __asm__ volatile("outb %0, %1": :"a"(data), "Nd" (port_num));
}

u8 Port_8bit::Read() {
    u8 result;
    __asm__ volatile("inb %1, %0": "=a" (result): "Nd" (port_num));
    return result;
}
// ---------------------------------------------- //
// Configuring 8bit slow port here
Port_8bit_Slow::Port_8bit_Slow(u16 port_num):Port_8bit(port_num) {

}
Port_8bit_Slow::~Port_8bit_Slow() {

}
void Port_8bit_Slow::Write(u8 data) {
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:": :"a"(data), "Nd" (port_num));
}
// ---------------------------------------------- //
// Configuring 16bit port here
Port_16bit::Port_16bit(u16 port_num):Port(port_num) {

}
Port_16bit::~Port_16bit() {

}
void Port_16bit::Write(u16 data) {
    __asm__ volatile("outw %0, %1": :"a"(data), "Nd" (port_num));
}

u16 Port_16bit::Read() {
    u16 result;
    __asm__ volatile("inw %1, %0": "=a" (result): "Nd" (port_num));
    return result;
}
// ---------------------------------------------- //
// Configuring 32bit port here
Port_32bit::Port_32bit(u32 port_num):Port(port_num) {

}
Port_32bit::~Port_32bit() {

}
void Port_32bit::Write(u32 data) {
    __asm__ volatile("outl %0, %1": :"a"(data), "Nd" (port_num));
}

u32 Port_32bit::Read() {
    u32 result;
    __asm__ volatile("inl %1, %0": "=a" (result): "Nd" (port_num));
    return result;
}
// ---------------------------------------------- //
