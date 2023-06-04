#include <stdio.h>
#include <raylib.h>

#include "screens.h"

Screen currentScreen;
static const int screenWidth = 800;
static const int screenHeight = 450;

int main(void) {
    InitWindow(screenWidth, screenHeight, "Pokemon Game");
    InitAudioDevice();

    initTitleScreen();

    SetTargetFPS(60);

    currentScreen = TITLE;
    while (!WindowShouldClose()) {
        switch (currentScreen) {
        case TITLE: updateTitleScreen(); break;
        case SETTINGS: printf("SETTINGS MENU SPAWN NOW\n"); break;
        default: break;
        }

        BeginDrawing();
        ClearBackground(WHITE);

        switch (currentScreen) {
        case TITLE: drawTitleScreen(); break;
        case SETTINGS: printf("DRAW SETTINGS SCREEN\n"); break;
        default: break;
        }

        EndDrawing();
    }

    unloadTitleScreen();

    CloseWindow();
    CloseAudioDevice();
    return 0;
}
