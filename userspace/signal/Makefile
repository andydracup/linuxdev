CC=gcc
CFLAGS=--std=c99
EXE=signal
SRC=signal.c
all: $(EXE)

$(EXE): $(SRC)
	@echo Building $@...
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@rm $(EXE)
