#ifndef SCREENS_H_
#define SCREENS_H_

#include <raylib.h>

// enum for current screen to switch to
typedef enum { TITLE, SETTINGS, MENU, BATTLE }Screen;

// current and previous screen enum
extern Screen currentScreen;
extern Screen prevScreen;
// global bg music
extern Music music;
// global volume setting for all music on bg
extern float volume;

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
