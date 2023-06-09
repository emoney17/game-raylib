#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <raylib.h>

#include "pokemon.h"

typedef struct {
    Pokemon *collection;
    Texture2D texture;
    int level;
    int xp;
    int pokeBalls;
    int greatBalls;
    int ultraBalls;
    int manaPot;
    int healthPot;
}Player;

extern Player player;

void initPlayer(void);
void printStats(void);
void updatePlayer(void);
void drawPlayer(void);
void unloadPlayer(void);

#endif // PLAYER_H
