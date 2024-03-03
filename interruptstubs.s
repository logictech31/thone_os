.section .text

.extern _ZN17Interrupt_Manager16handle_interruptEhj # Name mangling to the method interrupts.o 

.macro Handle_Interrupt_Rq interrupt_num
.global _ZN17Interrupt_Manager28handle_interrupt_request\num\Ev
    movb $\num, (interrupt_num)
    jmp int_bottom
.endm

.macro Handle_Interrupt_Ex interrupt_num
.global _ZN17Interrupt_Manager28handle_interrupt_request\num\Ev
    movb $\num, (interrupt_num)
    jmp int_bottom
.endm

Handle_Interrupt_Rq 0x00
Handle_Interrupt_Rq 0x01

# int_bottom jumps into the handle_interrupts function directly
int_bottom:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (interrupt_num)
    call _ZN17Interrupt_Manager16handle_interruptEhj
    # addl $5, %esp
    movl %eax, %esp

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

    iret

.data
    interrupt_num: .byte 0