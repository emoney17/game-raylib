#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screens.h"
#include "button.h"
#include "player.h"
#include "enemy.h"

#define NUM_OF_BUTTONS 4

static Texture2D background;
static Button *attackButton;
static Button *blockButton;
static Button *healthPotButton;
static Button *itemsButton;
static Button *settingsButton;
static Button *backButton;
static Sound failedPress;

static bool itemsMode = false; // mode to only show the items buttons
static Button *itemsScreenButtons[NUM_OF_BUTTONS];

static const char* buttonTexturePath = "resources/textures/button.png";
static const char* buttonSoundPath = "resources/audio/sound_button.ogg";

void initMenuScreen()
{
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
    // Create the base item buttons (4 at the bottom)
    for (int i = 0; i < NUM_OF_BUTTONS; i ++) {
        itemsScreenButtons[i] = createButton(NULL, buttonTexturePath, buttonSoundPath, x, y);
        printf("Item button %d created coords x: %f y: %f", i, x, y);
        x += 200;
    }
}

void updateMenuScreen()
{
    // Set the correct music
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

    updatePlayer();
    updateEnemy();

    // ITEM BUTTONS
    if (itemsMode) {
        for (int i = 0; i < NUM_OF_BUTTONS; i ++) {
            updateButton(itemsScreenButtons[i]);

            // If the item is the default item, show no item on the button
            if (player.items[i].damage == -1) {
                itemsScreenButtons[i]->title = NULL;
            }
            // else show the button title as the item name
            else {
                itemsScreenButtons[i]->title = player.items[i].name;
            }
            
            // If there is no item on the button
            if (itemsScreenButtons[i]->title == NULL) {
                if (itemsScreenButtons[i]->action) {
                    PlaySound(failedPress);
                    printf("This item button as no item\n");
                }
            }
            // If there is an item on the button
            else {
                if (itemsScreenButtons[i]->action) {

                    // TODO: test if its beter to make items take action points or not
                    PlaySound(player.items[i].sound);
                    enemy.hp -= player.items[i].damage;
                    printf("Player used %s, dealt %d damage\n", player.items[i].name, player.items[i].damage);
                    printf("Enemy hp %d\n", enemy.hp);
                    player.items[i].uses -= 1;
                    printf("Item has %d uses\n", player.items[i].uses);

                    // If the uses are now 0, reset item to default item
                    if (player.items[i].uses == 0) {
                        player.items[i] = itemCollection[0];
                    }
                }
            }
        }
        
        // update back button to leave items mode
        updateButton(backButton);

        if (backButton->action) {
            PlaySound(backButton->sound); 
            printf("leaving items menu\n");
            itemsMode = false;
        }
    }
    // NORMAL BUTTONS
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

    // update settings
    updateButton(settingsButton);

    if (settingsButton->action) {
        PlaySound(settingsButton->sound);
        printf("NOTICE: Settings button\n");
        prevScreen = currentScreen;
        currentScreen = SETTINGS;
        printf("NOTICE: Prev: %s Current: %s\n", screenAsString(prevScreen), screenAsString(currentScreen));
    }
}

void drawMenuScreen()
{
    DrawTexture(background, 0, 0, WHITE);

    drawEnemy();

    // always draw settings button
    drawButton(settingsButton);

    if (itemsMode) {
        for (int i = 0; i < NUM_OF_BUTTONS; i ++) {
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
}

void unloadMenuScreen()
{
    UnloadTexture(background);

    unloadButton(attackButton);
    unloadButton(blockButton);
    unloadButton(healthPotButton);
    unloadButton(itemsButton);
    unloadButton(settingsButton);
    unloadButton(backButton);

    // unload all buttons for item mode
    for (int i = 0; i < NUM_OF_BUTTONS; i ++) {
        unloadButton(itemsScreenButtons[i]);
    }

    unloadPlayer();
    unloadEnemy();
}
