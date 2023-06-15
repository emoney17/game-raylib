#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int damage;
    int uses;
    Sound sound;
    const char *name;
}Item;

extern Item *itemCollection;
extern int itemCollectionSize;

Item *createItem(int damage, int uses, const char *name, const char* soundPath);
void initItems(void);
void drawItems(void);
void unloadItems(void);
