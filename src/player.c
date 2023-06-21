#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "player.h"
#include "enemy.h"

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

// Function for using special and normal items
void useItem(Item *item)
{
    if (strcmp(item->name, "Restore") == 0) {
        // PlaySound(item->sound);
        player.action += 1;
        printf("You restored an action point total: %d\n", player.action);
        item->uses -= 1;
        printf("Remaining uses uses: %d\n", item->uses);
    }
    else if (strcmp(item->name, "Greater Heal") == 0) {
        // PlaySound(item->sound);
        player.hp += 30;
        printf("You restored 30 health current %d\n", player.hp);
        item->uses -= 1;
        printf("Remaining uses uses: %d\n", item->uses);
    }
    else {
        printf("Normal weapon, attacking enemy\n");
        enemy.hp -= item->damage;
        printf("Enemy hp %d\n", enemy.hp);
        item->uses -= 1;
        printf("Remaining uses: %d\n", item->uses);
    }

}

void initPlayer(void)
{
    // Create the item collection
    itemCollection[0] = *createItem(-1, 1, "NONE", "resources/audio/sound_attack1.ogg");
    itemCollection[1] = *createItem(15, 1, "Claymore", "resources/audio/sound_attack1.ogg");
    itemCollection[2] = *createItem(10, 1, "Dagger", "resources/audio/sound_attack3.ogg");
    itemCollection[3] = *createItem(20, 1, "Fireball", "resources/audio/sound_fire.ogg");
    itemCollection[4] = *createItem(0, 2, "Restore", "resources/audio/sound_spell2.ogg");
    itemCollection[5] = *createItem(0, 1, "Greater Heal", "resources/audio/sound_spell2.ogg");

    // Check if all items are created
    for (int i = 0; i < MAX_ITEMS_COLLECTION; i++) {
        printf("%s %d %d\n", itemCollection[i].name, itemCollection[i].damage, itemCollection[i].uses);
    }

    // Create the player
    player.cast = LoadSound("resources/audio/sound_spell.ogg");
    player.attack = LoadSound("resources/audio/sound_attack2.ogg");
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
