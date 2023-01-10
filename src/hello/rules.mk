OBJS := hello.o
C_SRC := hello.c
USER_MODE := yes

define RUN/$(TARGET)
	$(call RUN/user-default)
endef
