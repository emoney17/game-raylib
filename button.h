#ifndef BUTTON_H
#define BUTTON_H

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

typedef enum { NORMAL, PRESSED }State;

typedef struct {
    const char* title;
    Texture2D texture;
    Sound sound;
    float posX, posY;
    float textX, textY;
    bool action;
    State state;
    Rectangle bounds;
    Rectangle source;
    int frameHeight;
}Button;

Button *createButton(const char* title, const char* texturePath, const char *soundPath, float x, float y);
void updateButton(Button *button);
void drawButton(Button *button);
void unloadButton(Button *button);

#endif //BUTTON_H
