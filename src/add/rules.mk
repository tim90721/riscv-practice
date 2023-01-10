ASM_SRC := add.s
USER_MODE := no
OBJDUMP_FLAGS += -M no-aliases -M numeric

define RUN/$(TARGET)
	$(call RUN/system-default)
endef

define DEBUG/$(TARGET)
	$(call DEBUG/system-default)
endef
