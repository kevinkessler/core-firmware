# This file is a makefile included from the top level makefile which
# defines the sources built for the target.

# Define the prefix to this directory. 
# Note: The name must be unique within this build and should be
#       based on the root of the project
TARGET_CPAL_PATH = STM32_CPAL_Driver
TARGET_CPAL_SRC_PATH = $(TARGET_CPAL_PATH)/src

# Add tropicssl include to all objects built for this target
INCLUDE_DIRS +=  $(TARGET_CPAL_PATH)/inc
INCLUDE_DIRS +=  $(TARGET_CPAL_PATH)/devices/stm32f10x

# C source files included in this build.
CSRC += $(TARGET_CPAL_SRC_PATH)/cpal_hal.c
CSRC += $(TARGET_CPAL_SRC_PATH)/cpal_i2c.c
CSRC += $(TARGET_CPAL_SRC_PATH)/cpal_usercallback.c


# C++ source files included in this build.
CPPSRC +=

# ASM source files included in this build.
ASRC +=

