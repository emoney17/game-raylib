#include "player.h"
#include <raylib.h>

void initPlayer(void) {
    player.cast = LoadSound("resources/audio/sound_spell.ogg");
    player.attack = LoadSound("resources/audio/sound_attack.ogg");
    player.hp = 80;
    player.healthPots = 1;
    player.actionsPots = 1;
    player.action = 3;
    player.turn = true;
}

void updatePlayer(void) {
    NULL;
}

void drawPlayer(void) {
    NULL;
}

void unloadPlayer(void) {
    UnloadSound(player.cast);
    UnloadSound(player.attack);
}
