#include <stdio.h>
#include <raylib.h>

#include "screens.h"
#include "button.h"

static Texture2D background;
static Button *startButton;
static Button *quitButton;
static Button *settingsButton;

void initTitleScreen(void) {
    //initialize music here since its the first screen
    background = LoadTexture("resources/textures/menubg.png");
    music = LoadMusicStream("resources/audio/music_title.ogg");
    SetMusicVolume(music, 1.0);
    PlayMusicStream(music);

    startButton = createButton("Start", "resources/textures/button.png", "resources/audio/fx_button.ogg", 147, 350);
    quitButton = createButton("End", "resources/textures/button.png", "resources/audio/fx_button.ogg", 319, 350);
    settingsButton = createButton("Settings", "resources/textures/button.png", "resources/audio/fx_button.ogg", 491, 350);
}

void updateTitleScreen(void) {
    UpdateMusicStream(music);

    updateButton(startButton);
    updateButton(quitButton);
    updateButton(settingsButton);

    if (quitButton->action) {
        PlaySound(quitButton->sound);
        printf("Quit game\n");
    }

    if (startButton->action) {
        PlaySound(startButton->sound);
        printf("Start button working\n");
        prevScreen = currentScreen;
        currentScreen = MENU;
        printf("Prev: %d Current: %d\n", prevScreen, currentScreen);
    }

    if (settingsButton->action) {
        PlaySound(settingsButton->sound);
        printf("The settings are working\n");
        prevScreen = currentScreen;
        currentScreen = SETTINGS;
        printf("Prev: %d Current: %d\n", prevScreen, currentScreen);
    }
}

void drawTitleScreen(void) {
    DrawTexture(background, 0, 0, WHITE);

    drawButton(startButton);
    drawButton(quitButton);
    drawButton(settingsButton);
}

void unloadTitleScreen(void) {
    UnloadTexture(background);
    //unload music stream here and not in others
    UnloadMusicStream(music);

    unloadButton(startButton);
    unloadButton(quitButton);
    unloadButton(settingsButton);
}
