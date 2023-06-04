#include <stdio.h>
#include <raylib.h>

#include "screens.h"
#include "button.h"

static Texture2D background;
static Button *forageButton;
static Button *exploreButton;
static Button *travelButton;
static Button *statsButton;
static Button *settingsButton;
static Button *quitButton;

void initMenuScreen() {
    background = LoadTexture("resources/textures/menubg.png"); 

    forageButton = createButton("Forage", "resources/textures/button.png", "resources/audio/fx_button.ogg", 20, 100);
    exploreButton = createButton("Explore", "resources/textures/button.png", "resources/audio/fx_button.ogg", 220, 100);
    travelButton = createButton("Travel", "resources/textures/button.png", "resources/audio/fx_button.ogg", 420, 100);
    statsButton = createButton("View Stats", "resources/textures/button.png", "resources/audio/fx_button.ogg", 620, 100);
    settingsButton = createButton("Settings", "resources/textures/button.png", "resources/audio/fx_button.ogg", 20, 350);
    quitButton = createButton("Quit", "resources/textures/button.png", "resources/audio/fx_button.ogg", 620, 350);
}

void updateMenuScreen() {
    UpdateMusicStream(music);

    updateButton(forageButton);
    updateButton(exploreButton);
    updateButton(travelButton);
    updateButton(statsButton);
    updateButton(settingsButton);
    updateButton(quitButton);

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
        printf("Prev: %d Current: %d\n", prevScreen, currentScreen);
    }

    if (quitButton->action) {
        PlaySound(quitButton->sound);
        printf("Quit game to title screen\n");
        prevScreen = currentScreen;
        currentScreen = TITLE;
        printf("Prev: %d Current: %d\n", prevScreen, currentScreen);
    }
}

void drawMenuScreen() {
    DrawTexture(background, 0, 0, WHITE);

    drawButton(forageButton);
    drawButton(exploreButton);
    drawButton(travelButton);
    drawButton(statsButton);
    drawButton(settingsButton);
    drawButton(quitButton);
}

void unloadMenuScreen() {
    UnloadTexture(background);

    unloadButton(forageButton);
    unloadButton(exploreButton);
    unloadButton(travelButton);
    unloadButton(statsButton);
    unloadButton(settingsButton);
    unloadButton(quitButton);
}
