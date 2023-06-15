#include "player.h"

void initPlayer(void) {
    player.cast = LoadSound("resources/audio/sound_spell1.ogg");
    player.attack = LoadSound("resources/audio/sound_attack.ogg");
    player.hp = 80;
    player.healthPots = 1;
    player.actionsPots = 1;
    player.action = 3;
    player.turn = true;
    player.items = malloc(sizeof(Item) * 3);
}

void updatePlayer(void) {
    if (player.action <= 0) {
        printf("NOTICE: You are out of actions, it is now the enemy turn\n");
        player.turn = false;
        player.action = 3;
    }
}

void unloadPlayer(void) {
    UnloadSound(player.cast);
    UnloadSound(player.attack);
}
