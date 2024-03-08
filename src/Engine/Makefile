include ../../Makefile.in

SRC=$(shell find . -name '*.c')
OBJ=$(SRC:%=%.o)
CFLAGS=-Wall -Wextra -g

.PHONY: engine clean

engine: $(ENGINE)

clean:
	rm -f $(OBJ)
	rm -f $(ENGINE)

$(ENGINE): $(OBJ)
	@echo $(OBJ)
	@echo $(SRC)
	$(AR) -ru $@ $^

%.c.o: %.c
	@echo !== COMPILING $< ==!
	$(CC) $(CFLAGS) $< -o $@

