CC=gcc
CFLAGS=--std=c99
EXE=fork
SRC=fork.c
all: $(EXE)

$(EXE): $(SRC)
	@echo Building $@...
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@rm $(EXE)
