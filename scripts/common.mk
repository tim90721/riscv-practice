ifneq ($(strip $(V)),)
Q=
else
Q=@
endif

define MKDIR
	@echo "\tMKDIR\t$(1)"
	$(Q)mkdir -p $(1)
endef
