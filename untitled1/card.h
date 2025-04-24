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
