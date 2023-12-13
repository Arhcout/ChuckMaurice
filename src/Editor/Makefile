SRC_DIR=.

LIBS=$(EDITOR_LIBS)
CFLAGS=$(EDITOR_CFLAGS)
LDFLAGS=$(EDITOR_LDFLAGS)

a: $(EDITOR_OBJ)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@echo !== COMPILING $< ==!
	$(CC) $(CFLAGS) $< -o $@

