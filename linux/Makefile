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

CONTAINER_NAME = tilck
DOCKER = docker exec -w /root/host/SuOS/linux $(CONTAINER_NAME)
DOCKER_IT = docker exec -it -w /root/host/SuOS/linux $(CONTAINER_NAME)
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

QEMU_RUN := $(QEMU) -drive file=$(IMG),if=floppy -serial stdio

run: all
ifeq ($(SYSTEM), Darwin)
	(sleep 1 && osascript move.scpt) &
endif
	$(QEMU_RUN)

run-only:
	$(QEMU_RUN)

#START_ADDRESS = 0xc400
START_ADDRESS = 0x008200

#kernel: $(KERNEL)
#$(KERNEL):
kernel:
	$(MAKE) -C kernel build -j \
		debug_build=$(debug_build) START_ADDRESS=$(START_ADDRESS)

debug:
	$(MAKE) build debug_build=true
	$(QEMU_RUN) -s -S
	#$(QEMU) -drive file=$(IMG),if=floppy -gdb tcp:0.0.0.0:1234 -S
#	$(QEMU) -fda $(IMG) -s -S

info:
	@echo IMG:	$(IMG)
	@echo MACHINE:	$(MACHINE)
	@echo MAKE: $(MAKE)
	@make -C kernel info

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

docker_exec:
	$(DOCKER_IT) bash
docker_start:
	docker start $(CONTAINER_NAME)
	$(DOCKER) /etc/init.d/ssh start
docker_backup:
	docker commit $(CONTAINER_NAME) sucicada/su-linux-dev
docker_push: docker_backup
	docker push sucicada/su-linux-dev
docker_new:
	docker run -tid \
		--cap-add=SYS_PTRACE \
		--security-opt seccomp=unconfined \
		--platform linux/amd64 \
		-p 2222:22 \
		-p 21234:1234 \
		-v /Users/peng/PROGRAM/Docker:/root/host\
		--name tilck -d sucicada/su-linux-dev
