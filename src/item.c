#include "item.h"
#include <stdio.h>

Item *itemCollection;
int itemCollectionSize = 3;

Item *createItem(int damage, int uses, const char *name, const char* soundPath) {
    Item *item = malloc(sizeof(Item)); 
    item->damage = damage;
    item->uses = uses;
    item->name = name;
    item->sound = LoadSound(soundPath);
    return item;
}

void initItems(void) {
    itemCollection = malloc(sizeof(Item) * itemCollectionSize);
    itemCollection[0] = *createItem(10, 2, "Claymore", "/resources/audio/sound_attack.ogg");
    itemCollection[1] = *createItem(15, 1, "Dagger", "resources/audio/sound_attack.ogg");
    itemCollection[2] = *createItem(25, 1, "Fireball", "resources/audio/sound_fire.ogg");
}
