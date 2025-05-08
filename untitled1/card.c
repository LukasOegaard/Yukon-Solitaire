#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"

Card* create_card(char rank, Suit suit_char) {
    Suit suit;

    switch (suit_char) {
        case 'H': suit = HEARTS; break;
        case 'D': suit = DIAMONDS; break;
        case 'C': suit = CLUBS; break;
        case 'S': suit = SPADES; break;
        default: return NULL;  // ugyldig suit
    }

    Card* card = malloc(sizeof(Card));
    if (!card) return NULL;

    card->rank = rank;
    card->suit = suit;
    card->face_up = 0;
    card->next = NULL;
    return card;
}

void free_deck(Card* head) {
    while (head) {
        Card* temp = head;
        head = head->next;
        free(temp);
    }
}

char suit_to_char(Suit suit) {
    switch (suit) {
        case HEARTS: return 'H';
        case DIAMONDS: return 'D';
        case CLUBS: return 'C';
        case SPADES: return 'S';
        default: return '?';
    }
}

// Bruges til table/bordvisning – skjuler kort der er face_down
char* card_to_string(Card* card) {
    char* str = malloc(4);
    if (!card || !card->face_up) {
        strcpy(str, "[]");
    } else {
        snprintf(str, 4, "%c%c", card->rank, suit_to_char(card->suit));
    }
    return str;
}

// Bruges i show_deck() – viser ALLE kort uanset face_up
char* card_to_string_always(Card* card) {
    char* str = malloc(4);
    if (!card) {
        strcpy(str, "[]");
    } else {
        snprintf(str, 4, "%c%c", card->rank, suit_to_char(card->suit));
    }
    return str;
}
