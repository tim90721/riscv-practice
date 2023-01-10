ASM_SRC := li.s
USER_MODE := no

define RUN/$(TARGET)
	$(call RUN/system-default)
endef

define DEBUG/$(TARGET)
	$(call DEBUG/system-default)
endef
