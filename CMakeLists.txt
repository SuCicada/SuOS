cmake_minimum_required(VERSION 3.16)
project(SuOS C)

set(CMAKE_C_STANDARD 11)

# ======== include header ===========
file(GLOB KERNEL_SRC_DIRS "linux/kernel/src/*")

foreach (dir ${KERNEL_SRC_DIRS})
    message(STATUS include: ${dir})
    include_directories(${dir})
endforeach ()


# ======== add source files ===========
file(GLOB_RECURSE SOURCE_FILES
        "linux/kernel/src/*.c"
        "linux/kernel/src/*.h"
        )

add_executable(SuOS
            ${SOURCE_FILES}
        )

# ======== test ===========
include_directories(linux/test)

add_executable(test
        linux/test/test_utils.c
        linux/test/test_rbtree.c
        linux/test/test_arraymem.c
        linux/test/test_memory.c linux/test/utils_test.c)

add_definitions(-D__ASSEMBLER__)
