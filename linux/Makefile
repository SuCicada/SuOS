OUTPUT = output
BIN = bin
IMG = $(OUTPUT)/suos.img
OS_BIN = $(OUTPUT)/suos.bin
OUT_LST = $(OUTPUT)/suos.lst
OUT_FLOPPY = $(OUTPUT)/floppy.bin
KERNEL = kernel/$(OUTPUT)/kernel

EDIMG = $(BIN)/edimg.sh
TMP_DIR = /tmp/floppy
MOUNT = sudo mount
UMOUNT = sudo umount
UID = $(shell id -u)
GID = $(shell id -g)
MAKE = make --no-print-directory
# ====== debug
debug_build = false

# ==== QEMU =======
# QEMU = qemu-system-x86_64
MEMORY = 32768K
QEMU = qemu-system-i386
QEMU += -m $(MEMORY)

.PHONY: list clean kernel
all: build
build: kernel $(OS_BIN) $(IMG) copy
	@echo "=========================="
	@echo "|| build su_img success ||"
	@echo "=========================="

run: build
	$(QEMU) -drive file=$(IMG),if=floppy

kernel:
	$(MAKE) -C kernel build debug_build=$(debug_build)

debug:
	$(MAKE) build debug_build=true
#	$(QEMU) -drive file=$(IMG),if=floppy -gdb tcp:0.0.0.0:1234 -S
	$(QEMU) -fda $(IMG) -s -S

copy: $(IMG) $(KERNEL)
	mkdir -p $(TMP_DIR)
	$(MAKE) mount
#	cp $(OUT_FLOPPY) $(TMP_DIR)
	cp $(KERNEL) $(TMP_DIR)
	$(MAKE) umount

mount: $(IMG)
	$(MOUNT) -o loop,fat=12,uid=$(UID),gid=$(GID) $(IMG) $(TMP_DIR)

umount:
	$(UMOUNT) $(TMP_DIR)

$(OS_BIN) : suos.asm Makefile output
	nasm -g -o $@ -l $(OUT_LST) $<
# nasm -o $(OUT_FLOPPY) -l $(OUTPUT)/floppy.lst floppy.nas

$(IMG): $(OS_BIN) $(KERNEL)
# 制作一个 1.44MB 的文件用于作为软盘文件
	$(EDIMG) $< $@

$(OUTPUT):
	mkdir -p $(OUTPUT)

list:
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$'

clean:
	rm -fr $(OUTPUT)
	$(MAKE) -C kernel clean
