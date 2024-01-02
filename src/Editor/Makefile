SRC_DIR=.
CFLAGS=$(EDITOR_CFLAGS)

a: $(EDITOR_OBJ)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@echo !== COMPILING $< ==!
	$(CC) $(CFLAGS) $< -o $@

