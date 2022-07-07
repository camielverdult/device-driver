cmake_minimum_required(VERSION 3.18)

project(driver VERSION 1.0.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(MODULE_NAME Laar-Verdult-module)

# This CMakeList is heavily based on this:
# https://gitlab.com/christophacham/cmake-kernel-module/-/blob/master/CMakeLists.txt

add_definitions(-D__KERNEL__ -DMODULE)

execute_process(
        COMMAND uname -r
        OUTPUT_VARIABLE KERNEL_RELEASE
        OUTPUT_STRIP_TRAILING_WHITESPACE
)


find_path(
        KERNELHEADERS_DIR
        include/linux/user.h
        PATHS /usr/src/linux-headers-${KERNEL_RELEASE}
)

# Print out kernel (headers) info
message(STATUS "Kernel release: ${KERNEL_RELEASE}")
message(STATUS "Kernel headers: ${KERNELHEADERS_DIR}")

include_directories(
        ${KERNELHEADERS_DIR}/include
)

set(DRIVER_FILE "${MODULE_NAME}.ko")
set(KBUILD_CMD $(MAKE) -C ${KERNELHEADERS_DIR} modules M=${CMAKE_CURRENT_BINARY_DIR} src=${CMAKE_CURRENT_SOURCE_DIR})

FILE(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/Kbuild "${MODULE_NAME}-objs := main.o device_file.o\n obj-m := ${MODULE_NAME}.o")

# Add commands for loadig/unloading kernel modules
add_custom_command(OUTPUT ${DRIVER_FILE}
        COMMAND ${KBUILD_CMD}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS main.c device_file.c VERBATIM
        )

add_custom_target(driver
        ALL DEPENDS ${DRIVER_FILE}
        )

add_custom_target(load
        COMMAND insmod ./${MODULE_NAME}.ko
        )

add_custom_target(unload
        COMMAND rmmod ./${MODULE_NAME}.ko
        )



add_library(dummy
        main.c
        device_file.c
        )