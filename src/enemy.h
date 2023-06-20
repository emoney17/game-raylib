#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

#define MAX_ENEMY_COLLECTION 5

typedef struct {
    Texture2D texture;
    const char *name;
    Sound attack;
    Sound defeat;
    int hp;
    int damage;
    float posX, posY;
    bool turn;
}Enemy;

extern Enemy enemy;

static Enemy enemyCollection[MAX_ENEMY_COLLECTION];

Enemy *createEnemy(const char* name, int hp, int damage, const char* texturePath, const char* attackSoundPath, const char* defeatSoundPath);
void initEnemy(void);
void updateEnemy(void);
void drawEnemy(void);
void unloadEnemy(void);
