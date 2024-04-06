# Specific part of the Makefile
EXEC=stack_ex2

# Begin generic part of the Makefile
CC=gcc
CFLAGS= -Werror -Wextra -Wall
LDFLAGS=
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

ifeq ($(DEBUG),yes)
	CFLAGS += -g
	LDFLAGS =
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS =
endif

all: $(EXEC)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)

doc: stack.h main.c
	@doxygen documentation/TP1

# End generic part of the makefile

# List of target dependencies
main.o: stack.h
