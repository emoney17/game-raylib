#include "enemy.h"
#include "screens.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_ENEMY_COLLECTION 5

Enemy *createEnemy(const char *name, int hp, int damage, const char *texturePath, const char *attackSoundPath, const char* deathSoundPath)
{
    Enemy *enemy = malloc(sizeof(Enemy));
    enemy->name = name;
    enemy->texture = LoadTexture(texturePath);
    enemy->attack = LoadSound(attackSoundPath);
    enemy->defeat = LoadSound(deathSoundPath);
    enemy->damage = damage;
    enemy->hp = hp;
    enemy->turn = false;
    enemy->posX = ((float)screenWidth - (float)enemy->texture.width) / 2;
    enemy->posY = 100.0f;
    return enemy;
}

void initEnemy(void)
{
    enemyCollection[0] = *createEnemy("Goblin1", 10, 11, "resources/textures/enemy1.png", "resources/audio/sound_attack.ogg", "resources/audio/sound_death1.ogg");
    enemyCollection[1] = *createEnemy("Goblin2", 20, 12, "resources/textures/enemy2.png", "resources/audio/sound_attack.ogg", "resources/audio/sound_death1.ogg");
    enemyCollection[2] = *createEnemy("Goblin3", 25, 13, "resources/textures/enemy3.png", "resources/audio/sound_attack.ogg", "resources/audio/sound_death1.ogg");
    enemyCollection[3] = *createEnemy("Goblin4", 20, 14, "resources/textures/enemy4.png", "resources/audio/sound_attack.ogg", "resources/audio/sound_death1.ogg");
    enemyCollection[4] = *createEnemy("Goblin5", 15, 15, "resources/textures/enemy5.png", "resources/audio/sound_attack.ogg", "resources/audio/sound_death1.ogg");
    // Start at first enemy
    enemy = enemyCollection[0];
}

void updateEnemy(void)
{
    SetSoundVolume(enemy.defeat, volume);

    // TODO: Pause for some time before attacking/playing sound/dropping item/etc
    // Defeat enemy
    if (enemy.hp <= 0) {
        PlaySound(enemy.defeat);
        int rEnemy = rand() % MAX_ENEMY_COLLECTION;
        // printf("ENEMY: %s was killed, spawned in new enemy %s\n", enemy.name, enemyCollection[r].name);
        enemy = enemyCollection[rEnemy];

        int rItem = 1 + (rand() % (MAX_ITEMS_COLLECTION - 1)); // Ignore first item in collection
        printf("%s dropped\n", itemCollection[rItem].name);

        // Check if open inventory slots and give item
        bool check;
        for (int i = 0; i < MAX_ITEMS; i++) {
            check = false;
            if (player.items[i].damage == -1) { // check if the item is the default item
                printf("There is an open slot, adding item\n");
                player.items[i] = itemCollection[rItem];
                check = true;
                break;
            }
            else {
                printf("Slot %d is not open\n", i);
            }
        }

        if (!check) {
            printf("There are no slots open, you will not gain the item\n");
        }
    }
    
    // Enemy turn
    if (!player.turn) {
        PlaySound(player.attack);
        player.hp -= enemy.damage;
        // printf("ENEMY: %s has attacked and dealt %d damage\n", enemy.name, enemy.damage);
        player.turn = true;
    }
}

void drawEnemy(void)
{
    DrawTexture(enemy.texture, enemy.posX, enemy.posY, WHITE);
}

void unloadEnemy(void)
{
    for (int i = 0; i < MAX_ENEMY_COLLECTION; i++) {
        printf("Unloading and freeing enemy %s\n", enemyCollection[i].name);
        UnloadTexture(enemyCollection[i].texture);
        UnloadSound(enemyCollection[i].attack);
    }
}
