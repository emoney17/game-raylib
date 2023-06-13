#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

typedef struct {
    Texture2D texture;
    const char* name;
    Sound attack;
    Sound defeat;
    int hp;
    bool turn;
}Enemy;

extern Enemy enemy;

static Enemy *enemies;

Enemy *createEnemy(const char* name, int hp, const char* texturePath, const char* attackSoundPath, const char* defeatSoundPath);
void initEnemy(void);
void updateEnemy(void);
void drawEnemy(void);
void unloadEnemy(void);
