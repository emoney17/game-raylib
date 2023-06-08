#include <raylib.h>

#include "screens.h"
#include "button.h"

static Texture2D background;
static Button *volumeUpButton;
static Button *volumeDownButton;
static Button *backButton;
static Button *quitButton;

static const char* buttonTexturePath = "resources/textures/button.png";
static const char* buttonSoundPath = "resources/audio/sound_button.ogg";

void initSettingsScreen() {
    background = LoadTexture("resources/textures/menubg.png");

    volumeUpButton = createButton("Up", buttonTexturePath, buttonSoundPath, 100, 100);
    volumeDownButton = createButton("Down", buttonTexturePath, buttonSoundPath, 300, 100);
    backButton = createButton("Back", buttonTexturePath, buttonSoundPath, 100, 350);
    quitButton = createButton("Quit", buttonTexturePath, buttonSoundPath, 100, 400);
}

void updateSettingsScreen() {
    if (IsMusicStreamPlaying(titleMusic)) {
        SetMusicVolume(titleMusic, volume);
        UpdateMusicStream(titleMusic); 
    }
    else if (IsMusicStreamPlaying(battleMusic)) {
        SetMusicVolume(battleMusic, volume);
        UpdateMusicStream(battleMusic);
    }
    else if (IsMusicStreamPlaying(menuMusic)) {
        SetMusicVolume(menuMusic, volume);
        UpdateMusicStream(menuMusic);
    }

    updateButton(volumeUpButton);
    updateButton(volumeDownButton);
    updateButton(backButton);
    updateButton(quitButton);

    if (volumeUpButton->action) {
        volume += 0.1;
        printf("Increasing volume %f\n", volume);
        PlaySound(volumeUpButton->sound);
    }

    if (volumeDownButton->action) {
        volume -= 0.1;
        printf("Decreasing volume %f\n", volume);
        PlaySound(volumeDownButton->sound);
    }

    if (backButton->action) {
        PlaySound(backButton->sound);
        printf("Quitting back previous screen\n");
        currentScreen = prevScreen;
        printf("Prev: SETTINGS Current: %s\n", screenAsString(currentScreen));
    }

    if (quitButton->action) {
        PlaySound(quitButton->sound);
        printf("Quitting game\n");
        exitFlag = true;
    }
}

void drawSettingsScreen() {
    DrawTexture(background, 0, 0, WHITE);

    drawButton(volumeUpButton);
    drawButton(volumeDownButton);
    drawButton(backButton);
    drawButton(quitButton);
}

void unloadSettingsScreen() {
    UnloadTexture(background);

    unloadButton(volumeUpButton);
    unloadButton(volumeDownButton);
    unloadButton(backButton);
    unloadButton(quitButton);
}
