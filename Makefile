CC = gcc
CFLAGS= -Wall -Wextra
SRC = src/main.c src/title.c src/menu.c src/button.c src/settings.c
LIBS = -lraylib -lm

all:
	$(CC) $(SRC) $(LIBS) $(CFLAGS)
clean:
	$(RM) a.out
run: all
	./a.out
