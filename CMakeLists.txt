cmake_minimum_required(VERSION 3.16)
project(SuOS C)

set(CMAKE_C_STANDARD 11)

# ======== include header ===========

include_directories("linux/kernel/src/")

file(GLOB KERNEL_SRC_DIRS "linux/kernel/src/*")

foreach (dir ${KERNEL_SRC_DIRS})
    message(STATUS include: ${dir})
    include_directories(${dir})
endforeach ()


# ======== add source files ===========
#add_definitions(-D__ASSEMBLER__)

file(GLOB_RECURSE SOURCE_FILES
        "linux/kernel/src/*.c"
        "linux/kernel/src/*.h"
        "linux/kernel/src/*.S"
        "linux/kernel/src/*.asm"
        )
add_executable(SuOS
        ${SOURCE_FILES}
        )

# ======== font ===========
#add_executable(font
#    linux/tool/convHankakuTxt.c
#        )

# ======== test ===========


include("test.cmake")
