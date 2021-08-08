addr=0x7c00
OBJDIR=.

CFLAGS := $(CFLAGS) -O1 -fno-builtin -I$(OBJDIR) -MD                                                                                        
CFLAGS += -fno-omit-frame-pointer
CFLAGS += -Wall -Wno-format -Wno-unused -Werror -gstabs -m32

LDFLAGS=-m elf_i386

OUTPUT=output

build: kernel 

kernel: entry.o main.o screen.o 
	mv *.o *.d $(OUTPUT)
	cd $(OUTPUT) ;\
	ld $(LDFLAGS) -N -e start -Ttext $(addr) -o $@.out $^ ;\
	objdump -S $@.out >$@.asm ;\
	objcopy -S -O binary -j .text $@.out $@ 
	
entry.o: entry.S $(OUTPUT)
	gcc -nostdinc $(CFLAGS) -c -o $@ $<
	# mv $@ $(OUTPUT)
main.o: main.c
	@#对应《30天》中的bootpack.c
	gcc -nostdinc $(CFLAGS) -Os -c -o $@ $<
	# mv $@ $(OUTPUT)
screen.o: screen.c
	gcc -nostdinc $(CFLAGS) -c -o $@ $<
	# mv $@ $(OUTPUT)

run: kernel
	qemu-system-i386 -drive format=raw,file=kernel,if=floppy

clean:
	@rm -r $(OUTPUT) 
	@rm -f entry.o main.o screen.o kernel.out kernel.asm kernel *.d

$(OUTPUT): 
	mkdir -p $(OUTPUT)
