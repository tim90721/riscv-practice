CFLAGS += $(ARCH_CFLAGS) -g -Wall

ifeq ($(strip $(USER_MODE)),yes)
CFLAGS += -static
else
CFLAGS += -nostdlib -fno-builtin
endif

ifneq ($(strip $(OUTPUT_LD)),)
LD_FLAGS += -T $(OUTPUT_LD) -Wl,-Map=$(TARGET_BUILD_DIR)/$(TARGET).map
endif

ASM_OBJS := $(patsubst %.S,%.o,$(patsubst %.s,%.o,$(ASM_SRC)))
C_OBJS := $(patsubst %.c,%.o,$(C_SRC))
OBJS := $(ASM_OBJS) $(C_OBJS)

define C_TARGET_RULE
$(TARGET_BUILD_DIR)/$(patsubst %.c,%.o,$(1)): $(TARGET_SRC_DIR)/$(1)
	$(call COMPILE,$$^,$$@)
endef

define ASM_TARGET_RULE
$(TARGET_BUILD_DIR)/$(patsubst %.S,%.o,$(patsubst %.s,%.o,$(1))): $(TARGET_SRC_DIR)/$(1)
	$(call COMPILE,$$^,$$@)
endef

define COMPILE
	@echo "\tCC\t$$(@F)"
	$(Q)$(CC) $(CFLAGS) -c $(1) -o $(2)
endef

define LINK
	@echo "\tLINK\t$(@F)"
	$(Q)$(CC) $(CFLAGS) $(LD_FLAGS) $(1) -o $(2)
endef

define DISASSEMBLY
	@echo "\tOBJDUMP\t$(DUMP_OUT)"
	$(Q)$(OBJDUMP) $(OBJDUMP_FLAGS) $(TARGET_BUILD_DIR)/$(ELF_OUT) > $(TARGET_BUILD_DIR)/$(DUMP_OUT)
endef
