#ifndef POKEMON_H
#define POKEMON_H

typedef enum { NORMAL, FIRE, WATER, ELECTRIC, GRASS }Type;
typedef enum { COMMON, UNCOMMON, RARE, LEGENDARY }Rarity;

typedef struct {
    const char* name;
    const char* basicAttack;
    const char* heavyAttack;
    int evolution;
    int hp;
    int basicAttackDamage;
    int heavyAttackDamage;
    Type type;
    Rarity rarity;
}Pokemon;

#endif // POKEMON_H
