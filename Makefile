CPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

objs = loader.o kernel.o

%.o: %.cxx
	g++ $(CPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

thone_kernel.bin: linker.ld $(objs)
	ld $(LDPARAMS) -T $< -o $@ $(objs)

install: thone_kernel.bin
	sudo chmod +x $<
	sudo cp $< /boot/thone_kernel.bin