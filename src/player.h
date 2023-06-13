#include <stdio.h>
#include <raylib.h>

typedef struct {
    int hp;
    int action;
    Sound cast;
    Sound attack;
    int healthPots;
    int actionsPots;
    bool turn;
}Player;

extern Player player;

void initPlayer(void);
void unloadPlayer(void);
