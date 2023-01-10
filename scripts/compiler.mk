CC = $(CROSS_COMPILE)gcc
OBJDUMP = $(CROSS_COMPILE)objdump

ARCH ?= rv32g
ABI ?= ilp32d

ARCH_CFLAGS := -march=$(ARCH) -mabi=$(ABI)
OBJDUMP_FLAGS := -S -D
