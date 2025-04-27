#ifndef GAME_H
#define GAME_H

#include "card.h"

#define COLUMN_COUNT 7
#define FOUNDATION_COUNT 4

typedef struct Pile {
    Card* top;
} Pile;

extern Pile columns[COLUMN_COUNT];
extern Pile foundations[FOUNDATION_COUNT];

void deal_to_columns(Card** deck);
void display_game(void);

#endif // GAME_H
