#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "screens.h"
#include "button.h"
#include "player.h"
#include "enemy.h"

static Texture2D background;
static Button *attackButton;
static Button *blockButton;
static Button *healthPotButton;
static Button *backButton;
static Button *itemsButton;
static Button *settingsButton;
static Sound failedPress;

static const char* buttonTexturePath = "resources/textures/button.png";
static const char* buttonSoundPath = "resources/audio/sound_button.ogg";

// TODO: Make heal and action restore on same button and open up a new screen
// TODO: Make inventory screen when openint inventory
void initMenuScreen() {
    failedPress = LoadSound("resources/audio/sound_fail.ogg");

    background = LoadTexture("resources/textures/menubg.png"); 
    menuMusic = LoadMusicStream("resources/audio/music_menu.ogg");

    attackButton = createButton("Attack", buttonTexturePath, "resources/audio/sound_attack.ogg", 20, 390);
    blockButton = createButton("Block", buttonTexturePath, "resources/audio/sound_block.ogg", 220, 390);
    healthPotButton = createButton("Heal", buttonTexturePath, "resources/audio/sound_spell1.ogg", 420, 390);
    itemsButton = createButton("Items", buttonTexturePath, "resources/audio/sound_inventory.ogg", 620, 390);
    backButton = createButton("Back", buttonTexturePath, buttonSoundPath, 20, 20);
    settingsButton = createButton("Settings", buttonTexturePath, buttonSoundPath, 620, 20);
}

void updateMenuScreen() {
    if (IsMusicStreamPlaying(battleMusic)) {
        StopMusicStream(battleMusic);
    }
    else if (IsMusicStreamPlaying(titleMusic)) {
        StopMusicStream(titleMusic);
    }

    if (!IsMusicStreamPlaying(menuMusic)) {
        PlayMusicStream(menuMusic);
    }

    SetMusicVolume(menuMusic, volume);
    UpdateMusicStream(menuMusic);

    updatePlayer();
    updateEnemy();

    updateButton(attackButton);
    updateButton(blockButton);
    updateButton(healthPotButton);
    updateButton(backButton);
    updateButton(itemsButton);
    updateButton(settingsButton);

    SetSoundVolume(failedPress, volume);

    if (player.turn) {
        if (attackButton->action) {
            PlaySound(attackButton->sound);
            enemy.hp -= 5;
            player.action -= 1;
            printf("PLAYER: 5 damaged dealt to enemy\n");
        }
        
        if (blockButton->action) {
            PlaySound(blockButton->sound);
            printf("PLAYER: Blocking\n");
            printf("HEALTH: %d\n ACTIONS: %d\n ITEM[0]: %s\n", player.hp, player.action, player.items[0].name);
            player.action -=1;
        }
        
        if (healthPotButton->action) {
            if (player.hp == 100) {
                PlaySound(failedPress);
                printf("WARNING: Hp is allready full, a pot will not be used\n");
            }
            else {
                PlaySound(healthPotButton->sound);
                printf("PLAYER: Using health pot, HP was %d now %d\n", player.hp, player.hp + 10);
                player.hp += 10;
                player.healthPots -= 1;
                player.action -=1;
            }
        }
        
        if (itemsButton->action) {
            PlaySound(itemsButton->sound);
            printf("PLAYER: Items screen\n");
        }

    }
    else {
        if (attackButton->action) {
            PlaySound(failedPress);
            printf("WARNING: It is not the players turn\n");
        }
        
        if (blockButton->action) {
            PlaySound(failedPress);
            printf("WARNING: It is not the players turn\n");
        }
        
        if (healthPotButton->action) {
            PlaySound(failedPress);
            printf("WARNING: It is not the players turn\n");
        }
        
        if (itemsButton->action) {
            PlaySound(failedPress);
            printf("WARNING: It is not the players turn\n");
        }
    }

    if (backButton->action) {
        PlaySound(backButton->sound);
        prevScreen = currentScreen;
        currentScreen = TITLE;

        unloadPlayer();
        unloadEnemy();

        initPlayer();
        initEnemy();

        printf("NOTICE: Player data wiped\n");
        printf("NOTICE: Prev: %s Current: %s\n", screenAsString(prevScreen), screenAsString(currentScreen));
    }
    
    if (settingsButton->action) {
        PlaySound(settingsButton->sound);
        printf("NOTICE: Settings button\n");
        prevScreen = currentScreen;
        currentScreen = SETTINGS;
        printf("NOTICE: Prev: %s Current: %s\n", screenAsString(prevScreen), screenAsString(currentScreen));
    }
}

void drawMenuScreen() {
    DrawTexture(background, 0, 0, WHITE);

    drawEnemy();

    drawButton(attackButton);
    drawButton(blockButton);
    drawButton(healthPotButton);
    drawButton(backButton);
    drawButton(itemsButton);
    drawButton(settingsButton);
}

void unloadMenuScreen() {
    UnloadTexture(background);

    unloadButton(attackButton);
    unloadButton(blockButton);
    unloadButton(healthPotButton);
    unloadButton(backButton);
    unloadButton(itemsButton);
    unloadButton(settingsButton);

    unloadPlayer();
    unloadEnemy();
}
