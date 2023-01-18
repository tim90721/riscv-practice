ASM_SRC := \
	start.S
C_SRC := \
	kernel.c \
	uart.c \
	printf.c

USER_MODE := no
OBJDUMP_FLAGS += -M no-aliases
GDB_INIT := $(TARGET_SRC_DIR)/.gdbinit

CFLAGS += -I$(TARGET_SRC_DIR)/inc

define RUN/$(TARGET)
	$(call RUN/system-default)
endef

define DEBUG/$(TARGET)
	$(call DEBUG/system-default)
endef
