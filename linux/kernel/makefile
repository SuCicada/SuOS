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

# https://linux.die.net/man/1/ld
# https://sites.ualberta.ca/dept/chemeng/AIX-43/share/man/info/C/a_doc_lib/cmds/aixcmds3/ld.htm
kernel: entry.o main.o screen.o func.o 
	mv *.o $(OUTPUT)
	cd $(OUTPUT) ;\
	ld $(LDFLAGS) -N -e start -Ttext  $(addr) -o $@.out $^ ;\
	objdump -j .text -j .data -S $@.out >$@.asm ;\
	objcopy -j .text -j .data -O binary $@.out $@ 
	
	
entry.o: entry.S
	gcc $(CFLAGS) -c -o $@ $<
	objdump -S $@ > $(OUTPUT)/$@.asm ;

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


# screen.o: screen.c
# 	gcc $(CFLAGS) -c -o $@ $<
# 	# mv $@ $(OUTPUT)

func.o: func.asm
	nasm -g -f elf32 -o $@ $<

clean: 
	@rm -fr $(OUTPUT) 
	@rm -fr entry.o main.o screen.o kernel.out kernel.asm kernel *.d

$(OUTPUT): 
	mkdir -p $(OUTPUT)
