addr=0xc400

OUTPUT=output
OBJDIR=.

CFLAGS := $(CFLAGS) -O0  -I. -static-libgcc 
# CFLAGS += -nostdinc
# 不使用C语言的内建函数 
# CFLAGS += -fno-builtin
#  -MD                                                                                        
# CFLAGS += -fno-omit-frame-pointer
# 编译后显示所有警告
CFLAGS += -Wall -Wno-format -Wno-unused -Werror 
# debug info
CFLAGS += -gstabs
CFLAGS += -m32 -march=i486
CFLAGS += -std=c99  -fno-stack-protector -g


LDFLAGS = -m elf_i386  -nostdlib -nostdinc


SOURCE_FILES = asmfunc.asm asmfunc.h \
 	entry.S mmu.h \
	convHankakuTxt.c hankaku.txt \
	main.c color.c hankaku.h 
# 注意，顺序很重要，entry 要在第一个
OBJ_NAME = entry.o main.o asmfunc.o dsctbl.o int.o color.o
OBJ_FILES = $(patsubst %, $(OUTPUT)/%, $(OBJ_NAME))

.PHONY: clean $(OBJ_NAME) kernel success

kernel = $(OUTPUT)/kernel
default:
	make build

info:
	@echo OUTPUT: 		$(OUTPUT)
	@echo SOURCE_FILES: $(SOURCE_FILES)
	@echo OBJ_FILES: 	$(OBJ_FILES)
	@echo CFLAGS:    	$(CFLAGS)
	@echo ""

success:
	@echo "=========================="
	@echo "|| build kernel success ||"
	@echo "=========================="
	
sources: hankaku.h 
	
build: info $(OUTPUT) $(SOURCE_FILES) $(OBJ_NAME) $(kernel) success	


# https://linux.die.net/man/1/ld
# https://sites.ualberta.ca/dept/chemeng/AIX-43/share/man/info/C/a_doc_lib/cmds/aixcmds3/ld.htm
# .ONESHELL:
# SECTIONS = -j .text -j .data -j .rodata 
SECTIONS = 
$(kernel) : $(OBJ_FILES)
# -Ttext 代表, 所有代码起始地址为 0xc400 ,即 entry 开始的地址
	ld $(LDFLAGS) -N -e start -Ttext $(addr) -o $@.out $^ 
	objcopy $(SECTIONS) -O binary $@.out $@ 
	objdump $(SECTIONS) -S $@.out > $@.asm 
	../../bin/objconv.exe -fnasm $@.out $@2.asm 

# ========== source files 
$(OUTPUT)/asmfunc.o: asmfunc.asm
	nasm -g -f elf32 -o $@ $<
	
$(OUTPUT)/entry.o: entry.S mmu.h
	gcc $(CFLAGS) -c -o $@ $<
	objdump -S $@ > $(patsubst %.o, %.asm, $@)

$(OUTPUT)/main.o: main.c color.c hankaku.h asmfunc.h
	gcc $(CFLAGS) -c -o $@ $< 
	objdump -S $@ > $(patsubst %.o, %.asm, $@)
	../../bin/objconv.exe -fnasm $@ $(patsubst %.o, %2.asm, $@)

$(OUTPUT)/%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<
	objdump -S $@ > $(patsubst %.o, %.asm, $@)


convHankakuTxt = $(OUTPUT)/convHankakuTxt
hankaku.h: hankaku.txt $(convHankakuTxt)
	 $(convHankakuTxt) $< $@

$(convHankakuTxt): convHankakuTxt.c 
	gcc -o  $@ $<

$(OUTPUT): 
	mkdir -p $(OUTPUT)

# ===== action 

# 明确声明clean是"伪目标"
# make就不会去检查是否存在一个叫做clean的文件，而是每次运行都执行对应的命令。
.PHONY: clean
clean: 
	rm -frv $(OUTPUT) 
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
