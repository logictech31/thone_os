When a computer starts, it goes through POST (Power on Self Test).

Some prerequisites while writing an OS are:
- Having a Cross Compiler C/C++ or any other
- Some ASSEMBLY Knowledge and basic knowledge of registers/data structures
- An Assembler (as/nasm), and a linker (ld)
- A virtualizer (like VirtualBox/Qemu)
- Makefile
And ofcourse, an Editor.
Also in my case, I did not write my own Bootloader, and used GRUB for booting.

Also, while writing an Operating system, you might think, that the stdlib/ios is available, but no, it is not. You will have to download the source code yourself or write one on your own.

In this project, I might write some things myself to get a vivid understanding of how things actually work.

Now the most important files that help jump in the C++ code are:
1. loader.s
2. linker.ld
3. kernel.cxx (The actual C++ file where the kernel_main() is called)

*loader.s*
Firstly, as I am not writing my own bootloader, I will be using GRUB.
So for GRUB to understand if there is an OS that exists on the disk, it first needs to check through the MAGIC number (0x1badb002), set the Flags (1 << 0 | 1 << 1) and the Checksum = -(MAGIC + FLAGS)
![[Pasted image 20240128185903.png]]

We then set the code for section multiboot
And point to the kernel_main with the
```
.extern kernel_main
```
which is responsible for the jump

**The Multi-boot Structure**
A Multiboot2-compliant bootloader provides an [information structure](https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Boot-information-format) when the kernel boots. On x86, a physical pointer is stored in EBX, while the magic number is stored in EAX. It's a well-known practice to check the magic number to verify the bootloader passed the correct information. This physical pointer information structure is 8-byte aligned, and contains tags. These tags may contain useful information about the system, for example: [the memory map](https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Memory-map), [ELF sections of the image](https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#ELF_002dSymbols) and [information about the framebuffer](https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Framebuffer-info)
(Source: https://wiki.osdev.org/Multiboot)

*linker.ld*
We first set up the ENTRY point of the binary file where we:
- set its output format, output architecture (i386)
- select sections from different .o files

```
.data {
	...
}
```
Will take care of the constructors being called.

We tell the linker that the Discarding of various symbols and comments is okay by this piece of code.
```
/DISCARD/ : {

}
```

```
.text: {
  /* link the multiboot struct here */
  . = ALIGN(8);
  KEEP(*(.multiboot))
  /* place all of your code afterwards */
  *(.text)
}
```
This part of the code is responsible for telling the linker to start a file with the .multiboot section with proper alignment.

*thone_io.h*
Here, I will be adding the standard io functions like printf and cout.
The architecture of printing is done as so.
So while printing, we have to keep two things in mind, The bits that take care of the colour, and the actual value
Suppose I want to print the famous phrase, "Hello, World!". When we pass the char* to printf, it doesn't just see the value of "Hello, World!" in it, but the information of colour is also provided

The physical address of the monitor is: `0xb8000` in hexadecimal or `753664` in decimal
This is memory mapped IO. Where whatever we write at THAT address, we write on screen.

Since `VideoMemory` is `unsigned short`, it will be of `2MiB`.

To preserve the colour information,
we do the following
```
for(int i = 0; str[i] != '\0'; i++) {
	VIDEO_MEMORY[i] = (VIDEO_MEMORY[i] & 0xFF00) | str[i] 
}
```
Which will only change the value which is to be displayed and not the colour information


In the end, we make the kernel.bin and then add a menuentry in grub.cfg
```
menuentry 'Custom OS' {
	multiboot /boot/kernel.bin
	boot
}
```

To verify if your bin file is multiboot enabled, you can
```
grub-file --is-x86-multiboot myos.bin
```
Test it by running this command, and then echo $? or $status depending on your shell
If 0 is returned then yes, your binary file is multiboot enabled, otherwise, it is not.