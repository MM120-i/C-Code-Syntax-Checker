CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC = Checker.c
EXE = Checker

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXE)
