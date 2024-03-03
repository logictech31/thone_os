#include "includes/interrupts.hxx"
#include "includes/ios.hxx"

uint32_t Interrupt_Manager::handle_interrupt(uint8_t interrupt_num, uint32_t esp) {
    std::cout << "Interrupt!\n";

    return esp;
}

void Interrupt_Manager::handle_interrupt_request0x00() {

}

void Interrupt_Manager::handle_interrupt_request0x01() {

}