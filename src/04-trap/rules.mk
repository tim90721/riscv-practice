ASM_SRC := \
	start.S \
	entry.S
C_SRC := \
	kernel.c \
	uart.c \
	plic.c \
	printf.c \
	sched.c \
	trap.c

USER_MODE := no
OBJDUMP_FLAGS += -M no-aliases
GDB_INIT := $(TARGET_SRC_DIR)/.gdbinit

CFLAGS += -I$(TARGET_SRC_DIR)/inc
OUTPUT_LD := $(TARGET_SRC_DIR)/output.ld

define RUN/$(TARGET)
	$(call RUN/system-default)
endef

define DEBUG/$(TARGET)
	$(call DEBUG/system-default)
endef
