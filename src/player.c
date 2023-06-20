#include "player.h"
#include <raylib.h>
#include <stdio.h>

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
    itemCollection[0] = *createItem(-1, 1, "NONE", "resources/audio/sound_attack.ogg");
    itemCollection[1] = *createItem(15, 1, "Claymore", "resources/audio/sound_attack.ogg");
    itemCollection[2] = *createItem(10, 1, "Dagger", "resources/audio/sound_attack.ogg");
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

    // Set all player items to the default item
    for (int i = 0; i < MAX_ITEMS; i++) {
        player.items[i] = itemCollection[0];
    }
}

void updatePlayer(void)
{
    // check if player is out of actions
    if (player.action <= 0) {
        printf("NOTICE: You are out of actions, it is now the enemy turn\n");
        player.turn = false;
        player.action = 3;
    }

    // check if any items have no more uses
    // check all items every time or check right after using an item?
}

void unloadPlayer(void)
{
    UnloadSound(player.cast);
    UnloadSound(player.attack);

    // Free item collection sound
    for (int i = 0; i < MAX_ITEMS_COLLECTION; i++) {
        printf("Unloading and freeing item %s\n", itemCollection[i].name);
        UnloadSound(itemCollection[i].sound);
    }
}
