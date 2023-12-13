include Makefile.in

.PHONY: all clean debug_ed debug_mo editor motor 

all: motor editor

debug_ed: editor
	@$(GDB) $(EDITOR)

debug_mo: motor
	@$(GDB) $(EDITOR)

editor: $(EDITOR)
motor: $(MOTOR)

clean:
	rm -rf $(BUILD_DIR)/*
	rm -f $(EDITOR)
	rm -f $(MOTOR)

$(EDITOR):
	$(MAKE) -C $(EDITOR_SRC_DIR)
	@echo !== LINKING $^ ==!
	$(LD) $(LDFLAGS) $(EDITOR_OBJ) -o $@ $(LIBS) $(MOTOR)

$(MOTOR):
	$(MAKE) -C $(MOTOR_SRC_DIR)
	@echo !== CREATING ARCHIVE $^ ==!
	$(AR) -ru $@ $(MOTOR_OBJ)

