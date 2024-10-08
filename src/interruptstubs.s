.section .data
interrupt_number:
    .byte 0x00

received_interrupt:
    .ascii "Interrupt Received!"
    len_rec = . - received_interrupt
.set IRQ_BASE, 0x20

.section .text

.macro interrupt_print
    mov $1, %eax
    mov $1, %edi
    mov $received_interrupt, %esi
    mov $len_rec, %edx
    int $0x80
.endm

.extern _ZN17Interrupt_Manager16handle_interruptEhj

.macro HandleException num
.global _ZN17Interrupt_Manager19handle_interrupt_except\num\()Ev
_ZN17Interrupt_Manager19handle_interrupt_except\num\()Ev:
    movb $\num, (interrupt_number)
    jmp int_bottom
.endm
.macro HandleInterruptRequest num
.global _ZN17Interrupt_Manager26handle_interrupt_request\num\()Ev
_ZN17Interrupt_Manager26handle_interrupt_request\num\()Ev:
    movb $\num + IRQ_BASE, (interrupt_number)
    push $0
    jmp int_bottom
.endm

HandleException 0x00
HandleException 0x01
HandleException 0x02
HandleException 0x03
HandleException 0x04
HandleException 0x05
HandleException 0x06
HandleException 0x07
HandleException 0x08
HandleException 0x09
HandleException 0x0A
HandleException 0x0B
HandleException 0x0C
HandleException 0x0D
HandleException 0x0E
HandleException 0x0F
HandleException 0x10
HandleException 0x11
HandleException 0x12
HandleException 0x13
HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x02
HandleInterruptRequest 0x03
HandleInterruptRequest 0x04
HandleInterruptRequest 0x05
HandleInterruptRequest 0x06
HandleInterruptRequest 0x07
HandleInterruptRequest 0x08
HandleInterruptRequest 0x09
HandleInterruptRequest 0x0A
HandleInterruptRequest 0x0B
HandleInterruptRequest 0x0C
HandleInterruptRequest 0x0D
HandleInterruptRequest 0x0E
HandleInterruptRequest 0x0F
HandleInterruptRequest 0x31

int_bottom:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (interrupt_number)
    call _ZN17Interrupt_Manager16handle_interruptEhj
    add %esp, 6
    movl %eax, %esp
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa
.global _ZN17Interrupt_Manager22ignore_interrupt_requestEv
_ZN17Interrupt_Manager22ignore_interrupt_requestEv:
    iret
