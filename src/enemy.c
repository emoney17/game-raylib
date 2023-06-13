#include "enemy.h"
#include "screens.h"

Enemy *createEnemy(const char *name, int hp, const char *texturePath, const char *attackSoundPath, const char* deathSoundPath) {
    Enemy *enemy = malloc(sizeof(Enemy));

    enemy->name = name;
    enemy->texture = LoadTexture(texturePath);
    enemy->attack = LoadSound(attackSoundPath);
    enemy->defeat = LoadSound(deathSoundPath);
    enemy->hp = hp;
    enemy->turn = false;

    return enemy;
}

void initEnemy(void) {
    enemies = malloc(sizeof(Enemy) * 5);
    enemies[0] = *createEnemy("Goblin1", 10, "resources/textures/enemy1.png", "resources/audio/attack.ogg", "resources/audio/sound_death1.ogg");
    enemies[1] = *createEnemy("Goblin2", 10, "resources/textures/enemy2.png", "resources/audio/attack.ogg", "resources/audio/sound_death1.ogg");
    enemies[2] = *createEnemy("Goblin3", 10, "resources/textures/enemy3.png", "resources/audio/attack.ogg", "resources/audio/sound_death1.ogg");
    enemies[3] = *createEnemy("Goblin4", 10, "resources/textures/enemy4.png", "resources/audio/attack.ogg", "resources/audio/sound_death1.ogg");
    enemies[4] = *createEnemy("Goblin5", 10, "resources/textures/enemy5.png", "resources/audio/attack.ogg", "resources/audio/sound_death1.ogg");
    enemy = enemies[0];
}

void updateEnemy(void) {
    SetSoundVolume(enemy.defeat, volume);
    if (enemy.hp == 0) {
        PlaySound(enemy.defeat);
        int r = rand() % 5;
        printf("Enemy %s was killed, spawned in new enemy %s\n", enemy.name, enemies[r].name);
        enemy = enemies[r];
    }
}

void drawEnemy(void) {
    DrawTexture(enemy.texture, 0, 0, WHITE);
}

void unloadEnemy(void) {
    UnloadTexture(enemy.texture);
    UnloadSound(enemy.attack);

    if (enemies != NULL) {
        free(enemies);
        enemies = NULL;
    }
}
