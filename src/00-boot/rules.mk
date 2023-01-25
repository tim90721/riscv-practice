ASM_SRC := \
	start.S
C_SRC := \
	kernel.c
USER_MODE := no
OBJDUMP_FLAGS += -M no-aliases

CFLAGS += -I$(TARGET_SRC_DIR)/inc
LD_FLAGS += -Ttext=0x80000000

define RUN/$(TARGET)
	$(call RUN/system-default)
endef

define DEBUG/$(TARGET)
	$(call DEBUG/system-default)
endef
