.set IRQ_BASE, 20

.section .text

.extern _ZN11descriptors17Interrupt_Manager16handle_interruptEhj

.macro Handle_Interrupt_Request num
.global _ZN11descriptors17Interrupt_Manager28handle_interrupt_request\num\()Ev
_ZN11descriptors17Interrupt_Manager28handle_interrupt_request\num\()Ev:
    movb $\num + IRQ_BASE, (interrupt_num)
    jmp int_bottom
.endm

.macro Handle_Interrupt_Exception num
.global _ZN11descriptors17Interrupt_Manager28handle_interrupt_request\num\()Ev
_ZN11descriptors17Interrupt_Manager28handle_interrupt_request\num\()Ev:
    movb $\num, (interrupt_num)
    jmp int_bottom
.endm

handle_interrupt_request 0x00
handle_interrupt_request 0x01

int_bottom:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    # Call the handle_interrupt function to handle the interrupt
    pushl %esp
    push (interrupt_num)
    call _ZN11descriptors17Interrupt_Manager16handle_interruptEhj
    movl %eax, %esp

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa
    # We are done handling interrupts
    iret

.global _ZN11descriptors17Interrupt_Manager24ignore_interrupt_requestEv
_ZN11descriptors17Interrupt_Manager24ignore_interrupt_requestEv:
    iret

.data
    interrupt_num: .byte 0