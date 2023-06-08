#include <raylib.h>

#include "screens.h"
#include "button.h"

static Texture2D background;
static Button *forageButton;
static Button *exploreButton;
static Button *travelButton;
static Button *statsButton;
static Button *settingsButton;
static Button *backButton;

static const char* buttonTexturePath = "resources/textures/button.png";
static const char* buttonSoundPath = "resources/audio/sound_button.ogg";

void initMenuScreen() {
    background = LoadTexture("resources/textures/menubg.png"); 
    menuMusic = LoadMusicStream("resources/audio/music_menu.ogg");

    forageButton = createButton("Forage", buttonTexturePath, buttonSoundPath, 20, 100);
    exploreButton = createButton("Explore", buttonTexturePath, buttonSoundPath, 220, 100);
    travelButton = createButton("Travel", buttonTexturePath, buttonSoundPath, 420, 100);
    statsButton = createButton("View Stats", buttonTexturePath, buttonSoundPath, 620, 100);
    settingsButton = createButton("Settings", buttonTexturePath, buttonSoundPath, 20, 350);
    backButton = createButton("Back", buttonTexturePath, buttonSoundPath, 620, 350);
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

    updateButton(forageButton);
    updateButton(exploreButton);
    updateButton(travelButton);
    updateButton(statsButton);
    updateButton(settingsButton);
    updateButton(backButton);

    if (forageButton->action) {
        PlaySound(forageButton->sound);
        printf("Forage function\n");
    }

    if (exploreButton->action) {
        PlaySound(exploreButton->sound);
        printf("Explore function\n");
    }

    if (travelButton->action) {
        PlaySound(travelButton->sound);
        printf("Travel function\n");
    }

    if (statsButton->action) {
        PlaySound(statsButton->sound);
        printf("View stats function\n");
    }

    if (settingsButton->action) {
        PlaySound(settingsButton->sound);
        printf("The settings are working\n");
        prevScreen = currentScreen;
        currentScreen = SETTINGS;
        printf("Prev: %s Current: %s\n", screenAsString(prevScreen), screenAsString(currentScreen));
    }

    if (backButton->action) {
        PlaySound(backButton->sound);
        printf("Quit game to title screen\n");
        prevScreen = currentScreen;
        currentScreen = TITLE;
        printf("Prev: %s Current: %s\n", screenAsString(prevScreen), screenAsString(currentScreen));
    }
}

void drawMenuScreen() {
    DrawTexture(background, 0, 0, WHITE);

    drawButton(forageButton);
    drawButton(exploreButton);
    drawButton(travelButton);
    drawButton(statsButton);
    drawButton(settingsButton);
    drawButton(backButton);
}

void unloadMenuScreen() {
    UnloadTexture(background);

    unloadButton(forageButton);
    unloadButton(exploreButton);
    unloadButton(travelButton);
    unloadButton(statsButton);
    unloadButton(settingsButton);
    unloadButton(backButton);
}
