# Add the NASM assembly source file to your project

#set(ASM_SOURCE_FILE "${CMAKE_SOURCE_DIR}/linux/kernel/src/asmfunc/asmfunc.asm")
message("CMAKE_SOURCE_DIR is: ${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR is: ${CMAKE_BINARY_DIR}")
set(CMAKE_VERBOSE_MAKEFILE ON)

# Set the output file name for the generated object file
set(asmfunc0_o "asmfunc0.o")
set(asmfunc_s_o "asmfunc_s.o")
set(asmfunc_o "asmfunc.o")
set(asmfunc_S "${CMAKE_SOURCE_DIR}/linux/kernel/src/asmfunc/asmfunc.S")
# Compile the assembly source file using NASM
add_custom_command(
        OUTPUT ${asmfunc0_o}
        COMMAND nasm -g -f elf32 -o ${asmfunc0_o} ${CMAKE_SOURCE_DIR}/linux/kernel/src/asmfunc/asmfunc.asm
)
add_custom_command(
        OUTPUT ${asmfunc_s_o}
        COMMAND nasm -g -f elf32 -o ${asmfunc_s_o} ${CMAKE_SOURCE_DIR}/linux/kernel/src/asmfunc/asmfunc_s.asm
)

add_custom_command(
        OUTPUT ${asmfunc_o}
        COMMAND gcc -O0 -Wall -Wno-format -Wno-unused -m32 -march=i486 -std=c99 -fno-stack-protector -g -c -o ${asmfunc_o} ${asmfunc_S}
#        -gstabs
        #        DEPENDS ${ASM_SOURCE_FILE}
)


#include_directories(linux/test)
#file(GLOB KERNEL_SRC_DIRS "linux/kernel/src/*")
#foreach (dir ${KERNEL_SRC_DIRS})
#    message(STATUS include: ${dir})
#    include_directories(${dir})
#endforeach ()
#include_directories("/usr/include/x86_64-linux-gnu")
#include_directories("/usr/include")
#include_directories("/usr/include/sys/")
#include_directories("/opt/homebrew/include")

file(GLOB_RECURSE test_SOURCE_FILES
#        "linux/kernel/src/*.c"
#        "linux/kernel/src/*.h"
        #        "linux/kernel/src/mouse/*.c"
        #        "linux/kernel/src/mouse/*.h"
        "linux/kernel/src/*/*.c"
        "linux/kernel/src/*/*.h"
        #        "linux/kernel/src/asmfunc/asmfunc.S"
        #        "linux/kernel/src/*.asm"
        "linux/test/utils/*"
        )

set(EXCLUDE_DIRS
        "linux/kernel/src/hankaku"
        "linux/kernel/src/rbtree"
        "linux/kernel/src/tmp"
        "linux/kernel/src/log"
        "linux/kernel/src/memory"
        "linux/kernel/src/list"
        )

foreach (EXCLUDE_DIR ${EXCLUDE_DIRS})
    file(GLOB_RECURSE EXCLUDE_FILES "${EXCLUDE_DIR}/*")
    list(REMOVE_ITEM test_SOURCE_FILES ${EXCLUDE_FILES})
endforeach ()

set(test_SOURCE_FILES ${test_SOURCE_FILES}
#        ${asmfunc0_o}
#        ${asmfunc_s_o}
        )


#add_definitions(-I/usr/include/x86_64-linux-gnu)
#add_definitions(-I/opt/homebrew/include)
#add_definitions(-I/usr/include/sys)
link_directories("/opt/homebrew/lib")
include_directories("/opt/homebrew/include")
add_executable(mytest
#        linux/test/test0.c
        linux/test/test_screen.c
        ${test_SOURCE_FILES}
        )

set_target_properties(mytest PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})


target_link_libraries(mytest SDL2)

#add_compile_options(-Wno-pointer-to-int-cast)
#add_compile_options(-Wint-to-pointer-cast)
#add_compile_options(-Wvoid-pointer-to-int-cast)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}
        -Wno-pointer-to-int-cast
        -Wno-void-pointer-to-int-caste
        ")

enable_testing()

add_test(
        NAME mytest
        COMMAND $<TARGET_FILE:mytest>#
)
