#include "enemy.h"
#include "screens.h"
#include "player.h"

Enemy *createEnemy(const char *name, int hp, int damage, const char *texturePath, const char *attackSoundPath, const char* deathSoundPath) {
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

void initEnemy(void) {
    enemies = malloc(sizeof(Enemy) * 5);
    enemies[0] = *createEnemy("Goblin1", 10, 11, "resources/textures/enemy1.png", "resources/audio/sound_attack.ogg", "resources/audio/sound_death1.ogg");
    enemies[1] = *createEnemy("Goblin2", 10, 12, "resources/textures/enemy2.png", "resources/audio/sound_attack.ogg", "resources/audio/sound_death1.ogg");
    enemies[2] = *createEnemy("Goblin3", 10, 13, "resources/textures/enemy3.png", "resources/audio/sound_attack.ogg", "resources/audio/sound_death1.ogg");
    enemies[3] = *createEnemy("Goblin4", 10, 14, "resources/textures/enemy4.png", "resources/audio/sound_attack.ogg", "resources/audio/sound_death1.ogg");
    enemies[4] = *createEnemy("Goblin5", 10, 15, "resources/textures/enemy5.png", "resources/audio/sound_attack.ogg", "resources/audio/sound_death1.ogg");
    enemy = enemies[0];
}

void updateEnemy(void) {
    SetSoundVolume(enemy.defeat, volume);
    if (enemy.hp == 0) {
        PlaySound(enemy.defeat);
        int r = rand() % 5;
        printf("ENEMY: %s was killed, spawned in new enemy %s\n", enemy.name, enemies[r].name);
        enemy = enemies[r];
    }

    if (!player.turn) {
        PlaySound(player.attack);
        player.hp -= enemy.damage;
        printf("ENEMY: %s has attacked and dealt %d damage\n", enemy.name, enemy.damage);
        player.turn = true;
    }
}

void drawEnemy(void) {
    DrawTexture(enemy.texture, enemy.posX, enemy.posY, WHITE);
}

void unloadEnemy(void) {
    UnloadTexture(enemy.texture);
    UnloadSound(enemy.attack);

    if (enemies != NULL) {
        free(enemies);
        enemies = NULL;
        printf("ENEMY: Freed\n");
    }
    else {
        printf("ERROR: Could not free enemy\n");
    }
}
