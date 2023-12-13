SRC_DIR=.


LIBS=$(MOTOR_LIBS)
CFLAGS=$(MOTOR_CFLAGS)
LDFLAGS=$(MOTOR_LDFLAGS)

a: $(MOTOR_OBJ)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@echo !== COMPILING $< ==!
	$(CC) $(CFLAGS) $< -o $@

