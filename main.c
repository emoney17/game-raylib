#include <stdio.h>
#include <raylib.h>

#include "screens.h"

Screen currentScreen;
Screen prevScreen;
Music music;
float volume = 1.0;
static const int screenWidth = 800;
static const int screenHeight = 450;

int main(void) {
    InitWindow(screenWidth, screenHeight, "Pokemon Game");
    InitAudioDevice();

    initTitleScreen();
    initSettingsScreen();
    initMenuScreen();

    SetTargetFPS(60);

    currentScreen = TITLE;
    while (!WindowShouldClose()) {
        switch (currentScreen) {
        case TITLE: updateTitleScreen(); break;
        case SETTINGS: updateSettingsScreen(); break;
        case MENU: updateMenuScreen(); break;
        default: break;
        }

        BeginDrawing();
        ClearBackground(WHITE);

        switch (currentScreen) {
        case TITLE: drawTitleScreen(); break;
        case SETTINGS: drawSettingsScreen(); break;
        case MENU: drawMenuScreen();
        default: break;
        }

        EndDrawing();
    }

    unloadTitleScreen();
    unloadSettingsScreen();
    unloadMenuScreen();

    CloseWindow();
    CloseAudioDevice();
    return 0;
}
