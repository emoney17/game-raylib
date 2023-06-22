#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#define MAX_ITEMS 4
#define MAX_ITEMS_COLLECTION 6

typedef struct {
    const char *name;
    int damage;
    int uses;
    Sound sound;
} Item;

typedef struct {
    int hp;
    int action;
    int block;
    Sound cast;
    Sound attack;
    int healthPots;
    int actionsPots;
    bool turn;
    Item items[MAX_ITEMS];
} Player;

extern Player player;
extern Item itemCollection[MAX_ITEMS_COLLECTION];

Item *createItem(int damage, int uses, const char *name, const char* soundPath);
void useItem(Item *item);
void initPlayer(void);
void updatePlayer(void);
void unloadPlayer(void);

#endif // PLAYER_H
