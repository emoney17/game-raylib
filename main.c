#include <stdio.h>

#include <raylib.h>
#include "screens.h"

static const int screenWidth = 800;
static const int screenHeight = 450;

int main(void) {

    InitWindow(screenWidth, screenHeight, "Pokemon Game");
    InitAudioDevice();

    initTitleScreen();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        updateTitleScreen();
        drawTitleScreen();
    }

    unloadTitleScreen();

    return 0;
}
