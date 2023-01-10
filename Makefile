ROOT_DIR := $(PWD)
BUILD_DIR := $(ROOT_DIR)/build
SRC_DIR := $(ROOT_DIR)/src
SCRIPTS_DIR := $(ROOT_DIR)/scripts

CROSS_COMPILE ?= riscv32-unknown-elf-

include $(SCRIPTS_DIR)/common.mk
include $(SCRIPTS_DIR)/compiler.mk
include $(SCRIPTS_DIR)/qemu.mk
include $(SCRIPTS_DIR)/target.mk
include $(SCRIPTS_DIR)/gdb.mk

include $(TARGET_SRC_DIR)/rules.mk

USER_MODE ?= yes

include $(SCRIPTS_DIR)/build.mk

ELF_OUT := $(TARGET).elf
DUMP_OUT := $(patsubst %.elf,%.dump,$(ELF_OUT))

RUN/$(TARGET) ?= $(RUN/user-default)
PREPARE/$(TARGET) ?= $(PREPARE/user-default)

$(call PREPARE/$(TARGET))

all: $(TARGET_BUILD_DIR) $(TARGET_BUILD_DIR)/$(ELF_OUT)

$(TARGET_BUILD_DIR): $(BUILD_DIR)
	$(call MKDIR,$@)

$(BUILD_DIR):
	$(call MKDIR,$@)

$(TARGET_BUILD_DIR)/$(ELF_OUT): $(addprefix $(TARGET_BUILD_DIR)/,$(OBJS))
	$(call LINK,$^,$@)

$(foreach src,$(C_SRC),$(eval $(call C_TARGET_RULE,$(src))))
$(foreach src,$(ASM_SRC),$(eval $(call ASM_TARGET_RULE,$(src))))

.PHONY = run clean FORCE

FORCE:

run: all
	$(Q)$(call RUN/$(TARGET))

debug: all
	$(Q)$(call DEBUG/$(TARGET))

objdump: all
	$(Q)$(call DISASSEMBLY)

clean:
	@echo "\tCLEAN"
	$(Q)rm -rf build/
