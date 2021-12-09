addr=0xc400
OBJDIR=.

CFLAGS := $(CFLAGS) -nostdinc -O0  -I$(OBJDIR)
# 不使用C语言的内建函数 
CFLAGS += -fno-builtin
#  -MD                                                                                        
CFLAGS += -fno-omit-frame-pointer
# 编译后显示所有警告
CFLAGS += -Wall -Wno-format -Wno-unused -Werror 
# debug info
CFLAGS += -gstabs 
CFLAGS += -m32 -march=i486
CFLAGS += -std=c99  -fno-stack-protector -g


LDFLAGS=-m elf_i386

OUTPUT=output

build: $(OUTPUT) kernel 
	@echo build kernel over

kernel: entry.o main.o screen.o func.o 
	mv *.o $(OUTPUT)
	cd $(OUTPUT) ;\
	ld $(LDFLAGS) -N -e start -Ttext $(addr) -o $@.out $^ ;\
	objdump -S $@.out >$@.asm ;\
	objcopy -O binary -j .text $@.out $@ 
	# 
	
	
entry.o: entry.S
	gcc $(CFLAGS) -c -o $@ $<
	# mv $@ $(OUTPUT)
main.o: main.c 
	@#对应《30天》中的bootpack.c
	gcc $(CFLAGS) -c -o $@ $<
	objdump -S $@ > $(OUTPUT)/$@.asm ;

color.o: color.c
	gcc $(CFLAGS) -c -o output/$@ $<
	# objdump -S output/$@ > $(OUTPUT)/$@.asm ;
	../../bin/objconv.exe -fnasm output/$@
	 
color.S: color.c
	gcc $(CFLAGS) -c -S -o output/$@ $<


screen.o: screen.c
	gcc $(CFLAGS) -c -o $@ $<
	# mv $@ $(OUTPUT)
func.o: func.asm
	nasm -g -f elf32 -o $@ $<

# run: build
# 	qemu-system-i386 -drive format=raw,file=kernel,if=floppy

clean: 
	@rm -fr $(OUTPUT) 
	@rm -fr entry.o main.o screen.o kernel.out kernel.asm kernel *.d

$(OUTPUT): 
	mkdir -p $(OUTPUT)
