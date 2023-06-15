#include <stdio.h>
#include <raylib.h>

#include "item.h"

typedef struct {
    int hp;
    int action;
    int itemsSize;
    Sound cast;
    Sound attack;
    int healthPots;
    int actionsPots;
    bool turn;
    Item *items;
}Player;

extern Player player;

void initPlayer(void);
void updatePlayer(void);
void unloadPlayer(void);
