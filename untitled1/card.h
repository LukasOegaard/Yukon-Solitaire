// card.h
#ifndef CARD_H
#define CARD_H

typedef enum { CLUBS, DIAMONDS, HEARTS, SPADES } Suit;

typedef struct Card {
    char rank; // 'A', '2'...'9', 'T', 'J', 'Q', 'K'
    Suit suit;
    int face_up;
    struct Card* next;
} Card;

Card* create_card(char rank, Suit suit);
void free_deck(Card* head);
const char* suit_to_string(Suit suit);
char* card_to_string(Card* card); // e.g., "5D" or "[ ]"

#endif

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
void display_game();

#endif

