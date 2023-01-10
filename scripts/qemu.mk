QEMU_USR := $(Q)qemu-riscv32
QEMU_SYSTEM := $(Q)qemu-system-riscv32
QFLAGS_USER :=
QFLAGS_SYSTEM := -nographic -smp 1 -machine virt -bios none

define RUN/user-default
	@echo "\tUSR RUN\t$(ELF_OUT)\t"
	$(QEMU_USR) $(TARGET_BUILD_DIR)/$(ELF_OUT)
endef

define RUN/system-default
	@echo "\tSYS RUN\t$(ELF_OUT)\t"
	$(QEMU_SYSTEM) $(QFLAGS_SYSTEM) -kernel $(TARGET_BUILD_DIR)/$(ELF_OUT)
endef

define DEBUG/system-default
	@echo "\tSYS DBG\t$(ELF_OUT)\t"
	$(QEMU_SYSTEM) $(QFLAGS_SYSTEM) -kernel $(TARGET_BUILD_DIR)/$(ELF_OUT) -s -S &
	$(GDB) $(TARGET_BUILD_DIR)/$(ELF_OUT) $(GDB_FLAGS)
endef
