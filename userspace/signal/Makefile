CC=gcc
CFLAGS=--std=c99

all: signal

signal: signal.c
	@echo Building $@...
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@rm signal
