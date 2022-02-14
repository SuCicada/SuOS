cmake_minimum_required(VERSION 3.16)
project(SuOS C)

set(CMAKE_C_STANDARD 11)

include_directories(linux/kernel/src)
include_directories(linux/kernel/src/asmfunc)
include_directories(linux/kernel/src/color)
include_directories(linux/kernel/src/hankaku)
include_directories(linux/kernel/src/keyboard)
include_directories(linux/kernel/src/mouse)
include_directories(linux/kernel/src/queue)
include_directories(linux/kernel/src/utils)

include_directories(linux/test)

add_executable(SuOS
        linux/kernel/src/asmfunc/asmfunc.h
        linux/kernel/src/asmfunc/asmfunc.asm
        linux/kernel/src/asmfunc/asmfunc.S
        linux/kernel/src/color/color.c
        linux/kernel/src/color/color.h
        linux/kernel/src/hankaku/convHankakuTxt.c
        linux/kernel/src/hankaku/hankaku.h
        linux/kernel/src/keyboard/keyboard.c
        linux/kernel/src/keyboard/keyboard.h
        linux/kernel/src/mouse/mouse.c
        linux/kernel/src/mouse/mouse.h
        linux/kernel/src/queue/queue.c
        linux/kernel/src/queue/queue.h
        linux/kernel/src/utils/utils.c
        linux/kernel/src/utils/utils.h
        linux/kernel/src/dsctbl.c
        linux/kernel/src/header.h
        linux/kernel/src/int.c
        linux/kernel/src/main.c
        linux/kernel/src/mmu.h
        linux/test/test_utils.c
        linux/kernel/src/memory/memory.cpp linux/kernel/src/memory/memory.h linux/kernel/src/rbtree/rbtree.c linux/kernel/src/rbtree/rbtree.h linux/test/test_rbtree.c)

add_definitions(-D__ASSEMBLER__)



#add_executable(test_utils linux/test/test_utils.c)
