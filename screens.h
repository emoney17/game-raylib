#ifndef SCREENS_H_
#define SCREENS_H_

#include <raylib.h>

//TODO: Create button file for all buttons creation
typedef enum { TITLE, SETTINGS, BATTLE }Screen;

extern Screen currentScreen;

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
