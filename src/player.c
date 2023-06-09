#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

#include "player.h"
#include "pokemon.h"
#include "screens.h"

const int COLLECTION_SIZE = 2;

//Maybe init player like button, maybe not since there will only be 1 player
void initPlayer(void) {
    player.collection = malloc(sizeof(Pokemon) * COLLECTION_SIZE);
    player.texture = LoadTexture("resources/textures/player.png");
    player.level = 1;
    player.xp = 0;
    player.pokeBalls = 10;
    player.greatBalls = 2;
    player.ultraBalls = 0;
    player.healthPot = 2;
    player.manaPot = 2;
}

void printStats(void) {
    printf("Level: %d\n", player.level);
    printf("XP: %d\n", player.xp);
    printf("Health pots: %d\n", player.healthPot);
    printf("Mana pots: %d\n", player.manaPot);
    printf("Pokeballs: %d\n", player.pokeBalls);
    printf("Greatballs: %d\n", player.greatBalls);
    printf("Ultraballs: %d\n", player.ultraBalls);
    printf("Pokemon: \n");

    for (int i = 0; i < COLLECTION_SIZE; i++) {
        printf("\tPokemon %d\n", i);
    }
}

void updatePlayer(void) {
    
}

void drawPlayer(void) {
    if (currentScreen == MENU) {
        DrawTexture(player.texture, 0, 0, WHITE);
    }
    else if (currentScreen == BATTLE) {
        DrawTexture(player.texture, 0, 0, WHITE);
    }
}

void unloadPlayer(void) {
    UnloadTexture(player.texture);

    if (player.collection != NULL) {
        printf("PLAYER: ");
        free(player.collection);
        player.collection = NULL;
        printf("Free success\n");
    }
}
