#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "card.h"

Card* create_card(char rank, Suit suit) {
    Card* c = malloc(sizeof(Card));
    c->rank = rank;
    c->suit = suit;
    c->face_up = 0;
    c->next = NULL;
    return c;
}

void free_deck(Card* head) {
    while (head) {
        Card* temp = head;
        head = head->next;
        free(temp);
    }
}

const char* suit_to_string(Suit suit) {
    switch (suit) {
        case CLUBS: return "C";
        case DIAMONDS: return "D";
        case HEARTS: return "H";
        case SPADES: return "S";
        default: return "?";
    }
}

char* card_to_string(Card* card) {
    char* buf = malloc(4);
    if (!card->face_up) {
        strcpy(buf, "[ ]");
    } else {
        snprintf(buf, 4, "%c%s", card->rank, suit_to_string(card->suit));
    }
    return buf;
}
