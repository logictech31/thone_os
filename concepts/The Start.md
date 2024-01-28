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

Firstly, as I am not writing my own bootloader, I will be using GRUB.
So for GRUB to understand if there is an OS that exists on the disk, it first needs to check through the MAGIC number (0x1badb002), set the Flags (1 << 0 | 1 << 1) and the Checksum = -(MAGIC + FLAGS)
![[Pasted image 20240128185903.png]]

We then set the code for section multiboot
And point to the kernel_main with the
```
.extern kernel_main
```
which is responsible for the jump