// deck.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"

Card* load_deck(const char* filename);
void show_deck(Card* deck);

// deck.c (implementering)
Card* load_deck(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Message: File not found.\n");
        return NULL;
    }

    Card* head = NULL;
    Card* tail = NULL;
    char line[4];

    while (fgets(line, sizeof(line), f)) {
        char rank = line[0];
        char suit_char = line[1];
        Suit suit;
        switch (suit_char) {
            case 'C': suit = CLUBS; break;
            case 'D': suit = DIAMONDS; break;
            case 'H': suit = HEARTS; break;
            case 'S': suit = SPADES; break;
            default:
                printf("Message: Invalid suit '%c'\n", suit_char);
                fclose(f);
                free_deck(head);
                return NULL;
        }

        Card* c = create_card(rank, suit);
        if (!head) head = c;
        else tail->next = c;
        tail = c;
    }

    fclose(f);
    printf("Message: OK\n");
    return head;
}

void show_deck(Card* deck) {
    Card* curr = deck;
    while (curr) {
        char* str = card_to_string(curr);
        printf("%s ", str);
        free(str);
        curr = curr->next;
    }
    printf("\n");
}

#include <time.h> // til random
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "card.h"

void interleave_shuffle(Card** head, int split) {
    if (!head || !*head) return;

    Card* left = *head;
    Card* right = NULL;
    Card* temp = left;

    for (int i = 1; i < split && temp->next; i++) {
        temp = temp->next;
    }

    right = temp->next;
    temp->next = NULL;

    Card* new_head = NULL;
    Card** tail = &new_head;

    while (left || right) {
        if (left) {
            *tail = left;
            tail = &left->next;
            left = left->next;
        }
        if (right) {
            *tail = right;
            tail = &right->next;
            right = right->next;
        }
    }

    *tail = NULL;
    *head = new_head;
}

void random_shuffle(Card** head) {
    if (!head || !*head) return;

    // 1. Kopier kort til array for let adgang
    Card* array[52];
    int count = 0;
    Card* curr = *head;
    while (curr && count < 52) {
        array[count++] = curr;
        curr = curr->next;
    }

    // 2. Fisher-Yates shuffle
    srand(time(NULL));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card* tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    // 3. Genskab linked list
    for (int i = 0; i < count - 1; i++) {
        array[i]->next = array[i + 1];
    }
    array[count - 1]->next = NULL;
    *head = array[0];
}

void save_deck(Card* head, const char* filename) {
    FILE* f = fopen(filename ? filename : "cards.txt", "w");
    if (!f) {
        printf("Message: Could not open file for writing.\n");
        return;
    }

    Card* curr = head;
    while (curr) {
        fprintf(f, "%c%s\n", curr->rank, suit_to_string(curr->suit));
        curr = curr->next;
    }

    fclose(f);
    printf("Message: OK (deck saved)\n");
}
