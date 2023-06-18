#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "screens.h"
#include "button.h"
#include "player.h"
#include "enemy.h"

#define itemScreenNumberOfButtons 4

static Texture2D background;
static Button *attackButton;
static Button *blockButton;
static Button *healthPotButton;
static Button *itemsButton;
static Button *settingsButton;
static Button *backButton;
static Sound failedPress;

static bool itemsMode = false; // mode to only show the items buttons
static Button *itemsScreenButtons[itemScreenNumberOfButtons];

static const char* buttonTexturePath = "resources/textures/button.png";
static const char* buttonSoundPath = "resources/audio/sound_button.ogg";

// TODO: Make inventory screen when open inventory

void initMenuScreen() {
    failedPress = LoadSound("resources/audio/sound_fail.ogg");

    background = LoadTexture("resources/textures/menubg.png"); 
    menuMusic = LoadMusicStream("resources/audio/music_menu.ogg");

    attackButton = createButton("Attack", buttonTexturePath, "resources/audio/sound_attack.ogg", 20, 390);
    blockButton = createButton("Block", buttonTexturePath, "resources/audio/sound_block.ogg", 220, 390);
    healthPotButton = createButton("Heal", buttonTexturePath, "resources/audio/sound_spell1.ogg", 420, 390);
    itemsButton = createButton("Items", buttonTexturePath, "resources/audio/sound_inventory.ogg", 620, 390);
    
    settingsButton = createButton("Settings", buttonTexturePath, buttonSoundPath, 620, 20);
    backButton = createButton("Back", buttonTexturePath, buttonSoundPath, 620, 80);

    float x = 20;
    float y = 390;
    // itemsScreenButtons = malloc(sizeof(Button) * 4);
    for (int i = 0; i < itemScreenNumberOfButtons; i ++) {
        itemsScreenButtons[i] = createButton(NULL, buttonTexturePath, buttonSoundPath, x, y);
        printf("Item button %d created coords x: %f y: %f", i, x, y);
        x += 200;
    }
}

void updateMenuScreen() {
    if (IsMusicStreamPlaying(battleMusic)) {
        StopMusicStream(battleMusic);
    }
    else if (IsMusicStreamPlaying(titleMusic)) {
        StopMusicStream(titleMusic);
    }

    if (!IsMusicStreamPlaying(menuMusic)) {
        PlayMusicStream(menuMusic);
    }

    SetSoundVolume(failedPress, volume);
    SetMusicVolume(menuMusic, volume);
    UpdateMusicStream(menuMusic);

    // TODO: int update player, if an item has 0 uses remove it from the array
    updatePlayer();
    updateEnemy();

    // update the names of the item buttons based on the items the player has
    for (int i = 0; i < player.itemsSize - 1; i++) {
        if (player.items[i].name != NULL) {
            if (player.items[i].uses == 0) {
                itemsScreenButtons[i]->title = NULL;
            }
            else {
                itemsScreenButtons[i]->title = player.items[i].name;
            }
        }
    }
    
    if (itemsMode) {
        // update all buttons
        for (int i = 0; i < itemScreenNumberOfButtons; i ++) {
            updateButton(itemsScreenButtons[i]);
        }

        // if there is no item associated to the button play error sound
        for (int i = 0; i < itemScreenNumberOfButtons; i++) {
            if(itemsScreenButtons[i]->action) {
                if (itemsScreenButtons[i]->title == NULL) {
                    PlaySound(failedPress);
                    printf("You do not have an item\n");
                }
                else {
                    PlaySound(player.items[i].sound);
                    printf("using item %s\n", player.items[i].name);

                    // update hp and actions 
                    enemy.hp -= player.items[i].damage;
                    player.action -= 1;
                    player.items[i].uses -= 1;
                }
            }
        }

        //update back button to leave items mode
        updateButton(backButton);
        if (backButton->action) {
            PlaySound(backButton->sound); 
            printf("leaving items menu\n");
            itemsMode = false;
        }

    }
    else {
        updateButton(attackButton);
        updateButton(blockButton);
        updateButton(healthPotButton);
        updateButton(itemsButton);

        if (player.turn) {
            if (attackButton->action) {
                PlaySound(attackButton->sound);
                enemy.hp -= 5;
                player.action -= 1;
                printf("PLAYER: 5 damaged dealt to enemy\n");
            }
            
            // TODO: Make this the show stats button later
            if (blockButton->action) {
                PlaySound(blockButton->sound);
                printf("PLAYER: Blocking\n");
                printf("HEALTH: %d\nACTIONS: %d\n", player.hp, player.action);
                printf("ITEMS: \n");
                for (int i = 0; i < player.itemsSize - 1; i++) {
                    printf("%d %s\n", i, player.items[i].name);
                }
                // player.action -=1;
            }
            
            if (healthPotButton->action) {
                if (player.hp == 100) {
                    PlaySound(failedPress);
                    printf("WARNING: Hp is allready full, a pot will not be used\n");
                }
                else {
                    PlaySound(healthPotButton->sound);
                    printf("PLAYER: Using health pot, HP was %d now %d\n", player.hp, player.hp + 10);
                    player.hp += 10;
                    player.healthPots -= 1;
                    player.action -=1;
                }
            }
            
            if (itemsButton->action) {
                PlaySound(itemsButton->sound);
                printf("PLAYER: Items screen\n");
                itemsMode = true;
            }
            
        }
        else {
            if (attackButton->action) {
                PlaySound(failedPress);
                printf("WARNING: It is not the players turn\n");
            }
            
            if (blockButton->action) {
                PlaySound(failedPress);
                printf("WARNING: It is not the players turn\n");
            }
            
            if (healthPotButton->action) {
                PlaySound(failedPress);
                printf("WARNING: It is not the players turn\n");
            }
            
            if (itemsButton->action) {
                PlaySound(failedPress);
                printf("WARNING: It is not the players turn\n");
            }
        }
    }

    updateButton(settingsButton);
    if (settingsButton->action) {
        PlaySound(settingsButton->sound);
        printf("NOTICE: Settings button\n");
        prevScreen = currentScreen;
        currentScreen = SETTINGS;
        printf("NOTICE: Prev: %s Current: %s\n", screenAsString(prevScreen), screenAsString(currentScreen));
    }
}

void drawMenuScreen() {
    DrawTexture(background, 0, 0, WHITE);

    drawEnemy();

    if (itemsMode) {
        for (int i = 0; i < itemScreenNumberOfButtons; i ++) {
            drawButton(itemsScreenButtons[i]);
        }

        // draw back button for items mode to leave
        drawButton(backButton);
    }
    else {
        drawButton(attackButton);
        drawButton(blockButton);
        drawButton(healthPotButton);
        drawButton(itemsButton);
    }

    // always draw settings button
    drawButton(settingsButton);
}

void unloadMenuScreen() {
    UnloadTexture(background);

    unloadButton(attackButton);
    unloadButton(blockButton);
    unloadButton(healthPotButton);
    unloadButton(itemsButton);
    unloadButton(settingsButton);
    unloadButton(backButton);

    for (int i = 0; i < itemScreenNumberOfButtons; i ++) {
        unloadButton(itemsScreenButtons[i]);
    }

    unloadPlayer();
    unloadEnemy();
}
