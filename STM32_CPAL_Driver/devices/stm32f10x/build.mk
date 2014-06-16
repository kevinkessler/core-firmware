# This file is a makefile included from the top level makefile which
# defines the sources built for the target.

# Define the prefix to this directory. 
# Note: The name must be unique within this build and should be
#       based on the root of the project
TARGET_CPAL_DEVICE_PATH = STM32_CPAL_Driver/devices
TARGET_CPAL_DEVICE_SRC_PATH = $(TARGET_CPAL_DEVICE_PATH)/stm32f10x

# Add tropicssl include to all objects built for this target


# C source files included in this build.
CSRC += $(TARGET_CPAL_DEVICE_SRC_PATH)/cpal_i2c_hal_stm32f10x.c



# C++ source files included in this build.
CPPSRC +=

# ASM source files included in this build.
ASRC +=

