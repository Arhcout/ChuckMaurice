include ../../Makefile.in

SRC=$(shell find . -name '*.c')
OBJ=$(SRC:%=%.o)

LIBS=$(shell $$HOME/opt/SDL2/bin/sdl2-config --libs) -lSDL2_mixer -lSDL2_image -lSDL2_ttf
CFLAGS=$(shell $$HOME/opt/SDL2/bin/sdl2-config --cflags) -Wall -Wextra -g -I$(CURDIR)/../Engine

.PHONY: test clean

test: $(TEST)

clean:
	rm -f $(OBJ)
	rm -f $(TEST)

$(TEST): $(OBJ)
	$(LD) -g $(OBJ) -o $@ $(LIBS) $(ENGINE)

%.c.o: %.c
	@echo !== COMPILING $< ==!
	$(CC) $(CFLAGS) $< -o $@

