#include "item.h"
#include <stdio.h>

Item *itemCollection;

Item *createItem(int damage, int uses, const char *name, const char* soundPath) {
    Item *item = malloc(sizeof(Item)); 
    item->damage = damage;
    item->uses = uses;
    item->name = name;
    item->sound = LoadSound(soundPath);
    return item;
}

void initItems(void) {
    itemCollection = malloc(sizeof(Item) * 3);
    itemCollection[0] = *createItem(10, 2, "Claymore", "/resources/audio/sound_attack.ogg");
    itemCollection[1] = *createItem(15, 1, "Dagger", "resources/audio/sound_attack.ogg");
    itemCollection[2] = *createItem(25, 1, "Fireball", "resources/audio/sound_fire.ogg");

    int i = rand() % 3;
    printf("random item: %s\n", itemCollection[i].name);
    // for (int i = 0 ; i < 3; i++) {
    //     printf("%s\n", itemCollection[i].name);
    // }
}
