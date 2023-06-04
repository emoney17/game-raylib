#include <stdio.h>
#include <raylib.h>

#include "screens.h"
#include "button.h"

static Texture2D background;
static Button *volumeUpButton;
static Button *volumeDownButton;
static Button *quitButton;

void initSettingsScreen() {
    background = LoadTexture("resources/textures/menubg.png");
    //only need to init music once in title
    // music = LoadMusicStream("resources/audio/music_battle.ogg");
    // SetMusicVolume(music, volume);
    // PlayMusicStream(music);

    volumeUpButton = createButton("Up", "resources/textures/button.png", "resources/audio/fx_button.ogg", 100, 100);
    volumeDownButton = createButton("Down", "resources/textures/button.png", "resources/audio/fx_button.ogg", 300, 100);
    quitButton = createButton("Save & Quit", "resources/textures/button.png", "resources/audio/fx_button.ogg", 100, 350);
}

void updateSettingsScreen() {
    UpdateMusicStream(music); 

    updateButton(volumeUpButton);
    updateButton(volumeDownButton);
    updateButton(quitButton);

    if (volumeUpButton->action) {
        volume += 0.1;
        printf("Increasing volume %f\n", volume);
        SetMusicVolume(music, volume);
        PlaySound(volumeUpButton->sound);
    }

    if (volumeDownButton->action) {
        volume -= 0.1;
        printf("Decreasing volume %f\n", volume);
        SetMusicVolume(music, volume);
        PlaySound(volumeDownButton->sound);
    }

    if (quitButton->action) {
        PlaySound(quitButton->sound);
        printf("Quitting back previous screen\n");
        currentScreen = prevScreen;
        printf("Prev: %d Current: %d\n", prevScreen, currentScreen);
    }
}

void drawSettingsScreen() {
    DrawTexture(background, 0, 0, WHITE);

    drawButton(volumeUpButton);
    drawButton(volumeDownButton);
    drawButton(quitButton);
}

void unloadSettingsScreen() {
    UnloadTexture(background);
    // UnloadMusicStream(music); // only need to unload once

    unloadButton(volumeUpButton);
    unloadButton(volumeDownButton);
    unloadButton(quitButton);
}
