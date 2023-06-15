#ifndef SCREENS_H_
#define SCREENS_H_

#include <raylib.h>

//TODO: configure the 3 music streams to work on each screen

typedef enum { TITLE, SETTINGS, MENU, BATTLE }Screen;

typedef struct {
    const char* health;
    const char* actions;
    const char* warnings;
}Status;

// current and previous screen enum
extern Screen currentScreen;
extern Screen prevScreen;
// global bg music
extern Music titleMusic;
extern Music battleMusic;
extern Music menuMusic;
// global volume setting for all music on bg
extern float volume;
// global for exiting game
extern bool exitFlag;

// enum as string for logs
static const char* screenAsString(Screen s) {
    static const char* strings[] = { "TITLE", "SETTINGS", "MENU", "BATTLE" };
    return strings[s];
}

//TITLE SCREEN
void initTitleScreen(void);
void updateTitleScreen(void);
void drawTitleScreen(void);
void unloadTitleScreen(void);

//SETTINGS SCREEN
void initSettingsScreen(void);
void updateSettingsScreen(void);
void drawSettingsScreen(void);
void unloadSettingsScreen(void);

//BATTLE SCREEN
void initBattleScreen(void);
void updateBattleScreen(void);
void drawBattleScreen(void);
void unloadBattleScreen(void);

//MENU SCREEN
void initMenuScreen(void);
void updateMenuScreen(void);
void drawMenuScreen(void);
void unloadMenuScreen(void);

#endif // SCREENS_H_
