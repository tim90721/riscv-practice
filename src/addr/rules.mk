ASM_SRC := addr.s
USER_MODE := no
OBJDUMP_FLAGS += -M no-aliases -M numeric
LD_FLAGS += -Ttext=0x80000000

define RUN/$(TARGET)
	$(call RUN/system-default)
endef

define DEBUG/$(TARGET)
	$(call DEBUG/system-default)
endef
