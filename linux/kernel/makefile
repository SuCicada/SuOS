addr=0xc400

OUTPUT=output
OBJDIR=.

CFLAGS := $(CFLAGS) -nostdinc -O0  -I.
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


LDFLAGS = -m elf_i386
SOURCE_FILES = func.asm asmfunc.h \
 	entry.S mmu.h \
	convHankakuTxt.c hankaku.txt \
	main.c color.c hankaku.h 

OBJ_NAME =  main.o entry.o func.o
OBJ_FILES = $(patsubst %, $(OUTPUT)/%, $(OBJ_NAME))

.PHONY: clean $(OBJ_NAME) kernel

build: info $(OUTPUT) sources $(OBJ_NAME) kernel 
	@echo "=========================="
	@echo "|| build kernel success ||"
	@echo "=========================="

info:
	@echo OUTPUT: 		$(OUTPUT)
	@echo SOURCE_FILES: $(SOURCE_FILES)
	@echo OBJ_FILES: 	$(OBJ_FILES)
	@echo CFLAGS:    	$(CFLAGS)
	@echo ""

# https://linux.die.net/man/1/ld
# https://sites.ualberta.ca/dept/chemeng/AIX-43/share/man/info/C/a_doc_lib/cmds/aixcmds3/ld.htm

sources: hankaku.h 
	
# .ONESHELL:
kernel: $(OBJ_FILES)
	# cd $(OUTPUT)
	ld $(LDFLAGS) -N -e start -Ttext $(addr) -o $@.out $^
	objdump -j .text -j .data -S $@.out > $@.asm 
	objcopy -j .text -j .data -O binary $@.out $@ 

# ========== source files 
func.o: func.asm
	nasm -g -f elf32 -o $(OUTPUT)/$@ $<
	
entry.o: entry.S mmu.h
	gcc $(CFLAGS) -c -o $(OUTPUT)/$@ $<
	objdump -S $(OUTPUT)/$@ > $(OUTPUT)/$*.asm

main.o: main.c color.c hankaku.h 
	gcc $(CFLAGS) -c -o $(OUTPUT)/$@ $<
	objdump -S $(OUTPUT)/$@ > $(OUTPUT)/$*.asm

hankaku.h: hankaku.txt convHankakuTxt
	$(OUTPUT)/convHankakuTxt hankaku.txt $@

convHankakuTxt: convHankakuTxt.c 
	gcc -o $(OUTPUT)/$@ $<

$(OUTPUT): 
	mkdir -p $(OUTPUT)

# ===== action 

# 明确声明clean是"伪目标"
# make就不会去检查是否存在一个叫做clean的文件，而是每次运行都执行对应的命令。
.PHONY: clean
clean: 
	rm -fr $(OUTPUT) 
	@# @rm -fr entry.o main.o screen.o kernel.out kernel.asm kernel *.d


# $(OUTPUT)/color.o: color.c
# 	gcc $(CFLAGS) -c -o output/$@ $<

# 	@# objdump -S output/$@ > $(OUTPUT)/$@.asm ;
# 	@# ../../bin/objconv.exe -fnasm output/$@
	 
# # temp for debug
# color.S: color.c
# 	gcc $(CFLAGS) -c -S -o output/$@ $<




# screen.o: screen.c
# 	gcc $(CFLAGS) -c -o $@ $<
# 	# mv $@ $(OUTPUT)
