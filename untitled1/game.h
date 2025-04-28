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

// Basale spilfunktioner
void deal_to_columns(Card** deck);
void display_game(void);
void clear_columns(void);

// Flyt kort
Card* cut_cards_from_column(int src_col, char rank, char suit);
void add_cards_to_column(int dst_col, Card* stack);

// Regeltjek
int is_valid_move(Card* moving_card, Card* destination_card);
int is_valid_foundation_move(Card* moving_card, Card* foundation_top);

// Hjælpefunktioner
void add_card_to_foundation(int foundation_num, Card* card);
int is_red(Suit suit);
int rank_to_value(char rank);

#endif
