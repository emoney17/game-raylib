#include <raylib.h>

#include "screens.h"
#include "player.h"
#include "enemy.h"

Player player;
Enemy enemy;
Screen currentScreen;
Screen prevScreen;
Music titleMusic;
Music battleMusic;
Music menuMusic;
float volume = 1.0;
bool exitFlag = false;

static const int screenWidth = 800;
static const int screenHeight = 450;

int main(void) {
    InitWindow(screenWidth, screenHeight, "Pokemon Game");
    InitAudioDevice();

    initPlayer();
    initEnemy();
    initTitleScreen();
    initSettingsScreen();
    initMenuScreen();

    // Disable ESC to exit
    SetExitKey(0);

    SetTargetFPS(60);
    currentScreen = TITLE;
    while (!WindowShouldClose() && !exitFlag) {
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
