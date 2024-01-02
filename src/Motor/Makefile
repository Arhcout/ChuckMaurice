SRC_DIR=.
CFLAGS=$(MOTOR_CFLAGS)

a: $(MOTOR_OBJ)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@echo !== COMPILING $< ==!
	$(CC) $(CFLAGS) $< -o $@

