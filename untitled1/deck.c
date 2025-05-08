// ==== card.h ====
#ifndef CARD_H
#define CARD_H

typedef enum { CLUBS, DIAMONDS, HEARTS, SPADES } Suit;

typedef struct Card {
    char rank;
    Suit suit;
    int face_up;
    struct Card* next;
} Card;

Card* create_card(char rank, Suit suit);
void free_deck(Card* head);
const char* suit_to_string(Suit suit);
char* card_to_string(Card* card);
char suit_to_char(Suit suit);

#endif


// ==== deck.h ====
#ifndef DECK_H
#define DECK_H

#include "card.h"

Card* load_deck(const char* filename);
void show_deck(Card* deck);
void interleave_shuffle(Card** head, int split);
void random_shuffle(Card** head);
void save_deck(Card* head, const char* filename);

#endif


// ==== deck.c ====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.h"
#include "card.h"

Card* load_deck(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Message: File not found.\n");
        return NULL;
    }

    char line[10];
    int count = 0;
    Card* head = NULL;
    Card* tail = NULL;

    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) < 2) continue;
        char rank = line[0];
        char suit_char = line[1];
        Suit suit;

        switch (suit_char) {
            case 'C': suit = CLUBS; break;
            case 'D': suit = DIAMONDS; break;
            case 'H': suit = HEARTS; break;
            case 'S': suit = SPADES; break;
            default:
                printf("Message: Invalid suit '%c'.\n", suit_char);
                fclose(file);
                free_deck(head);
                return NULL;
        }

        Card* card = create_card(rank, suit);
        if (!card) {
            fclose(file);
            free_deck(head);
            return NULL;
        }

        if (!head) head = card;
        else tail->next = card;
        tail = card;
        count++;
    }

    fclose(file);

    if (count != 52) {
        printf("Message: Invalid number of cards (%d). Must be 52.\n", count);
        free_deck(head);
        return NULL;
    }

    return head;
}

void show_deck(Card* deck) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    Card* current = deck;
    int col = 0;

    while (current) {
        for (int i = 0; i < 7; i++) {
            if (current) {
                current->face_up = 1;
                char* s = card_to_string(current);
                printf("%s\t", s);
                free(s);
                current = current->next;
            } else {
                printf("\t");
            }
        }
        printf("\n");
    }
}

void interleave_shuffle(Card** head, int split) {
    printf("Message: Interleave shuffle not yet implemented.\n");
}

void random_shuffle(Card** head) {
    printf("Message: Random shuffle not yet implemented.\n");
}

void save_deck(Card* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Message: Could not open file to save.\n");
        return;
    }

    Card* current = head;
    while (current) {
        fprintf(file, "%c%c\n", current->rank, suit_to_char(current->suit));
        current = current->next;
    }

    fclose(file);
    printf("Message: Deck saved to %s.\n", filename);
}
