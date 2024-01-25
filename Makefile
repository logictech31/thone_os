CPARAMS = -m32 -mkernel
ASPARAMS = --32
LDPARAMS = -melf_i386
objs = loader.o kernel.o

%.o: %.c
	gcc $(CPARAMS) -o $? -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

thone_kernel.bin: linker.ld $(objs)
	ld $(LDPARAMS) -T $< -o $(objs)