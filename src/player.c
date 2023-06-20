#include "player.h"
#include <stdio.h>

// TODO: make max items 4, fill with null when no item

Item itemCollection[MAX_ITEMS_COLLECTION];

Item *createItem(int damage, int uses, const char *name, const char* soundPath)
{
    Item *item = malloc(sizeof(Item));
    item->damage = damage;
    item->uses = uses;
    item->name = name;
    item->sound = LoadSound(soundPath);
    return item;
}

void initPlayer(void)
{
    // Create the item collection
    itemCollection[0] = *createItem(1, 1, "NONE", "resources/audio/sound_attack.ogg");
    itemCollection[1] = *createItem(15, 1, "Claymore", "resources/audio/sound_attack.ogg");
    itemCollection[2] = *createItem(10, 2, "Dagger", "resources/audio/sound_attack.ogg");
    itemCollection[3] = *createItem(20, 1, "Fireball", "resources/audio/sound_fire.ogg");

    // Check if all items are created
    for (int i = 0; i < MAX_ITEMS_COLLECTION; i++) {
        printf("%s %d %d\n", itemCollection[i].name, itemCollection[i].damage, itemCollection[i].uses);
    }

    // Create the player
    player.cast = LoadSound("resources/audio/sound_spell1.ogg");
    player.attack = LoadSound("resources/audio/sound_attack.ogg");
    player.hp = 80;
    player.healthPots = 1;
    player.actionsPots = 1;
    player.action = 3;
    player.turn = true;
}

void updatePlayer(void)
{
    if (player.action <= 0) {
        printf("NOTICE: You are out of actions, it is now the enemy turn\n");
        player.turn = false;
        player.action = 3;
    }
}

void unloadPlayer(void)
{
    UnloadSound(player.cast);
    UnloadSound(player.attack);
}
