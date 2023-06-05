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
MEMORY = 32M # 32768K
QEMU = qemu-system-i386

ifeq ($(SYSTEM), Darwin)
	QEMU = osascript move.scpt & $(QEMU)
endif


QEMU += -m $(MEMORY)

DOCKER = docker exec -w /root/host/SuOS/linux tilck
DOCKER_IT = docker exec -it -w /root/host/SuOS/linux tilck
MACHINE := $(shell uname -m)
SYSTEM  := $(shell uname -s)
ifeq ($(MACHINE),x86_64)
	GDB = gdb
else ifeq ($(MACHINE),arm64)
	MAKE := $(DOCKER) $(MAKE)
	GDB = x86_64-elf-gdb
endif

test:
	echo -$(MAKEFLAGS)

.PHONY: list clean kernel info test
all: build

build:
	@$(MAKE) _build
_build: info img  # copy
	@echo "=========================="
	@echo "|| build su_img success ||"
	@echo "=========================="

run: all
ifeq ($(SYSTEM), Darwin)
	osascript move.scpt &
endif
	$(QEMU) -drive file=$(IMG),if=floppy -serial stdio

run-only:
	$(QEMU) -drive file=$(IMG),if=floppy

#START_ADDRESS = 0xc400
START_ADDRESS = 0x008200

#kernel: $(KERNEL)
#$(KERNEL):
kernel:
	$(MAKE) -C kernel build -j \
		debug_build=$(debug_build) START_ADDRESS=$(START_ADDRESS)

debug:
	$(MAKE) build debug_build=true
	$(QEMU) -drive file=$(IMG),if=floppy -gdb tcp:0.0.0.0:1234 -S
	#$(QEMU) -fda $(IMG) -s -S

info:
	@echo IMG:	$(IMG)
	@echo MACHINE:	$(MACHINE)
	@echo MAKE: $(MAKE)

copy: $(IMG) $(KERNEL)
# 使用copy方式的话, kernel 地址为 0xc400
	mkdir -p $(TMP_DIR)
	$(MAKE) mount
	cp $(OUT_FLOPPY) $(TMP_DIR)
	cp $(KERNEL) $(TMP_DIR)
	$(MAKE) umount

mount: $(IMG)
	$(MOUNT) -o users,loop,fat=12,uid=$(UID),gid=$(GID) $(IMG) $(TMP_DIR)

umount:
	$(UMOUNT) $(TMP_DIR)

$(OS_BIN): suos.asm Makefile output
	nasm -g -o $@ -l $(OUT_LST) $<
# nasm -o $(OUT_FLOPPY) -l $(OUTPUT)/floppy.lst floppy.nas

img: kernel $(IMG)
$(IMG): $(OS_BIN) $(KERNEL)
# 制作一个 1.44MB 的文件用于作为软盘文件
	$(EDIMG) $^ $@

$(OUTPUT):
	mkdir -p $(OUTPUT)

list:
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$'

clean:
	rm -fr $(OUTPUT)
	$(MAKE) -C kernel clean

exec_docker:
	$(DOCKER_IT) bash
