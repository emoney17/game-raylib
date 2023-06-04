#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

#include "screens.h"
#include "button.h"

static Texture2D title;
static Rectangle titleDest;
static Music music;
static Button *startButton;
static Button *endButton;
static Button *settingsButton;

void initTitleScreen(void) {
    title = LoadTexture("resources/textures/menubg.png");
    music = LoadMusicStream("resources/audio/music_title.ogg");
    SetMusicVolume(music, 0.4);
    PlayMusicStream(music);

    startButton = createButton("Start", "resources/textures/button.png", "resources/audio/fx_button.ogg", 100, 350);
    endButton = createButton("End", "resources/textures/button.png", "resources/audio/fx_button.ogg", 300, 350);
    settingsButton = createButton("Settings", "resources/textures/button.png", "resources/audio/fx_button.ogg", 500, 350);
}

void updateTitleScreen(void) {
    UpdateMusicStream(music);
    updateButton(startButton);
    updateButton(endButton);
    updateButton(settingsButton);

    if (endButton->action) {
        printf("End button\n");
        PlaySound(endButton->sound);
    }

    if (startButton->action) {
        printf("Start button\n");
        PlaySound(startButton->sound);
    }

    if (settingsButton->action) {
        printf("The settings are working\n");
        PlaySound(settingsButton->sound);
        currentScreen = SETTINGS;
    }
}

void drawTitleScreen(void) {
    DrawTexture(title, 0, 0, WHITE);

    drawButton(startButton);
    drawButton(endButton);
    drawButton(settingsButton);
}

void unloadTitleScreen(void) {
    UnloadTexture(title);
    UnloadMusicStream(music);
    unloadButton(startButton);
    unloadButton(endButton);
    unloadButton(settingsButton);
}
