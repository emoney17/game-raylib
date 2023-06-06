#include "screens.h"
#include "button.h"
#include <raylib.h>

static Texture2D background;
static Button *startButton;
static Button *quitButton;
static Button *settingsButton;

static const char* buttonTexturePath = "resources/textures/button.png";
static const char* buttonSoundPath = "resources/audio/sound_button.ogg";

void initTitleScreen(void) {
    //initialize music here since its the first screen
    background = LoadTexture("resources/textures/menubg.png");
    titleMusic = LoadMusicStream("resources/audio/music_title.ogg");

    startButton = createButton("Start", buttonTexturePath, buttonSoundPath, 147, 350);
    quitButton = createButton("Quit", buttonTexturePath, buttonSoundPath, 319, 350);
    settingsButton = createButton("Settings", buttonTexturePath, buttonSoundPath, 491, 350);
}

void updateTitleScreen(void) {
    if (!IsMusicStreamPlaying(titleMusic)) {
        PlayMusicStream(titleMusic);
    }

    SetMusicVolume(titleMusic, volume);
    UpdateMusicStream(titleMusic);

    updateButton(startButton);
    updateButton(quitButton);
    updateButton(settingsButton);

    if (quitButton->action) {
        PlaySound(quitButton->sound);
        printf("Quiting game\n");
        exitFlag = true; 
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
    UnloadMusicStream(titleMusic);

    unloadButton(startButton);
    unloadButton(quitButton);
    unloadButton(settingsButton);
}
