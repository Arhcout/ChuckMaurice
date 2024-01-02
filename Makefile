include Makefile.in

.PHONY: all clean debug_ed editor motor

all: motor editor

debug_ed: editor
	@$(GDB) $(EDITOR)

editor: $(EDITOR)
motor: $(MOTOR)

clean:
	rm -rf $(BUILD_DIR)/*
	rm -f $(EDITOR)
	rm -f $(MOTOR)

$(EDITOR): 
	$(MAKE) -C $(EDITOR_SRC_DIR)
	@echo !== LINKING ==!
	$$HOME/opt/SDL2/bin/sdl2-config --libs
	$(LD) $(LDFLAGS) $(EDITOR_OBJ) -o $@ $(EDITOR_LIBS) $(MOTOR)

$(MOTOR): 
	$(MAKE) -C $(MOTOR_SRC_DIR)
	@echo !== CREATING ARCHIVE ==!
	$(AR) -ru $@ $(MOTOR_OBJ)
