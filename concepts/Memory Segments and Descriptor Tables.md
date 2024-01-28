Now when it comes to memory segments exist as Kernel Space (sudo) and User Space (less privileges).

A common approach of attacking in the past was to load a program in the user's memory section and make it affect the Kernel space.

Today, the CPU is told it's privilege whether it can execute a piece of code in the *Data Segment* or not.

Now when we are in user space and press a key on the keyboard, 
1. It creates a triggered
2. The controller in the port communicates with the CPU
This is called as an *"Interrupt"*

- CPU will then stop working at the program to handle the keyboard interrupt.
- To handle this we have to write an *Interrupt Descriptor Table (IDT)*
- We then need to jump to the IDT and as well as switch the *memory segment*.
- IDT will switch access rights and jump to the kernel space to get the user input.
To create these *"segments"* we need to create a *Global Descriptor Tables*
which will define CS:DS stack

In total, it is 8 bytes long (64 bits)

![[Pasted image 20240128224527.png]]
