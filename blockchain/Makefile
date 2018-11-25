EXE=blockchain
OBJS=blockchain.o

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXE) -lcrypto

%.o:%.c
	$(CC) $(CFLAGS) -Wall -c $<
	
.PHONY: clean

clean:
	@rm -f $(OBJS) $(EXE)
