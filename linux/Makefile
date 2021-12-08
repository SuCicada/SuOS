OUTPUT = output
BIN = bin
OUT_IMG = $(OUTPUT)/suos.img
IMG = $(OUT_IMG)
OUT_BIN = $(OUTPUT)/suos.bin
OUT_LST = $(OUTPUT)/suos.lst
OUT_FLOPPY = $(OUTPUT)/floppy.bin 
KERNEL = kernel/$(OUTPUT)/kernel

# QEMU = qemu-system-x86_64
QEMU = qemu-system-i386
EDIMG = $(BIN)/edimg.sh
TMP_DIR = /tmp/floppy
MOUNT = sudo mount
UMOUNT = sudo umount 
UID = $(shell id -u)
GID = $(shell id -g)

build: $(IMG) build_kernel copy
	@echo over
	
build_kernel: 
	make $(KERNEL)
$(KERNEL):
	# nasm -o bootloader suos.nas
	cd ./kernel;make clean;make build addr=0xc400 

# $(KERNEL):
# 	cd ./kernel
# 	make clean
# 	make run addr=0xc400 


prerun: clean build
run: prerun
	$(QEMU) -drive file=$(IMG),if=floppy
debug: 
	$(QEMU) -drive file=$(IMG),if=floppy -gdb tcp:0.0.0.0:1234 -S

copy: $(IMG) $(KERNEL)
	mkdir -p $(TMP_DIR)
	make mount
	# cp $(OUT_FLOPPY) $(TMP_DIR)
	cp $(KERNEL) $(TMP_DIR)
	make umount

mount: $(IMG)
	$(MOUNT) -o loop,fat=12,uid=$(UID),gid=$(GID) $(IMG) $(TMP_DIR)

umount:	
	$(UMOUNT) $(TMP_DIR) 

$(OUT_BIN) : suos.nas Makefile output
	nasm -o $@ -l $(OUT_LST) $<   
	# nasm -o $(OUT_FLOPPY) -l $(OUTPUT)/floppy.lst floppy.nas

$(IMG): $(OUT_BIN)  
	$(EDIMG) $< $@

$(OUTPUT): 
	mkdir -p $(OUTPUT)

.PHONY: list

list:
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$'
clean:
	@rm -fr $(OUTPUT) 
	cd ./kernel;make clean
