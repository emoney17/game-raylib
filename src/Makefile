CC = gcc
CFLAGS= -Wall -Wextra
SRC = main.c title.c menu.c button.c settings.c player.c enemy.c
LIBS = -lraylib -lm

all:
	$(CC) $(SRC) $(LIBS) $(CFLAGS)
clean:
	$(RM) a.out
run: all
	./a.out
