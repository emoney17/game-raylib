#include <stdio.h>
#include <raylib.h>

#include "screens.h"

static Texture2D title;
static Rectangle titleDest;
static Music music;
static Texture2D button;
static Sound fx_button;

typedef enum { NORMAL, PRESSED }State;

State buttonState = NORMAL;
bool buttonAction = false;

void initTitleScreen(void) {
    title = LoadTexture("resources/textures/menubg.png");
    music = LoadMusicStream("resources/audio/music_title.ogg");
    SetMusicVolume(music, 1.0f);
    PlayMusicStream(music);

    button = LoadTexture("resources/textures/button.png");
    fx_button = LoadSound("resources/audio/fx_button.ogg");
}

void updateTitleScreen(void) {

    UpdateMusicStream(music);

    Vector2 mousePoint = GetMousePosition();
    Rectangle buttonBounds = { 0, 0, (float)button.width, (float)button.height };

    buttonAction = false;

    //clicking buttons
    if (CheckCollisionPointRec(mousePoint, buttonBounds)) {

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            buttonState = PRESSED;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            buttonAction = true;
            buttonState = NORMAL;
        }
    }
    else {
        buttonState = NORMAL;
    }

    //do button actions here
    if (buttonAction) {
        printf("Button pressed. Audio should play here.\n");
        PlaySound(fx_button);
    }
}

void drawTitleScreen(void) {

    int buttonFrameHeight = (float)button.height / 2;
    Rectangle buttonSource = { 0, 0, (float)button.width, buttonFrameHeight };

    BeginDrawing();
    ClearBackground(WHITE);

    DrawTexture(title, 0, 0, WHITE);

    buttonSource.y = buttonState * buttonFrameHeight;
    DrawTextureRec(button, buttonSource, (Vector2){0, 0}, WHITE);

    EndDrawing();
}

void unloadTitleScreen(void) {
    UnloadTexture(title);
    UnloadTexture(button);
    UnloadMusicStream(music);
    UnloadSound(fx_button);
}
