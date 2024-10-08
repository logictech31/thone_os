CPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386
VIRTUALIZER = qemu-system-i386

objs = objs/loader.o objs/gdt.o objs/kernel.o objs/port.o objs/ios.o objs/interruptstubs.o objs/interrupts.o

objs/%.o: src/%.cxx
	g++ $(CPPARAMS) -o $@ -c $<

objs/%.o: src/%.s
	as $(ASPARAMS) -o $@ $<

thone_kernel.bin: src/linker.ld $(objs)
	ld $(LDPARAMS) -T $< -o $@ $(objs)

install: thone_kernel.bin
	sudo chmod +x $<
	sudo cp $< /boot/thone_kernel.bin

thone_os.iso: thone_kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "Thone_OS" {' >> iso/boot/grub/grub.cfg
	echo 'multiboot /boot/thone_kernel.bin' >> iso/boot/grub/grub.cfg
	echo 'boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub2-mkrescue --output=$@ iso
	rm -rf iso/

run: thone_os.iso
	(killall qemu-kvm) || true
	$(VIRTUALIZER) -drive format=raw,file=thone_os.iso

.PHONY: clean
clean:
	rm -f objs/*
	rm -f *.bin
	rm -f *.iso
