ASM_SRC := li.s
USER_MODE := no
LD_FLAGS += -Ttext=0x80000000

define RUN/$(TARGET)
	$(call RUN/system-default)
endef

define DEBUG/$(TARGET)
	$(call DEBUG/system-default)
endef
