// deck.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"

Card* load_deck(const char* filename);
void show_deck(Card* deck);

// deck.c (implementering)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"

Card* load_deck(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    Card* head = NULL;
    Card* tail = NULL;
    char line[10];

    while (fgets(line, sizeof(line), file)) {
        char rank, suit;

        // Fjern newline
        line[strcspn(line, "\r\n")] = 0;

        if (strlen(line) != 2) {
            fclose(file);
            free_deck(head);
            return NULL;
        }

        rank = line[0];
        suit = line[1];

        Card* new_card = create_card(rank, suit);
        if (!new_card) {
            fclose(file);
            free_deck(head);
            return NULL;
        }

        if (!head) {
            head = tail = new_card;
        } else {
            tail->next = new_card;
            tail = new_card;
        }
    }

    fclose(file);
    return head;
}


#include <stdio.h>
#include "deck.h"
#include "card.h"

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
        fprintf(f, "%c%s\n", curr->rank, suit_to_char(curr->suit));
        curr = curr->next;
    }

    fclose(f);
    printf("Message: OK (deck saved)\n");
}

#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "card.h"

void show_deck(Card* head) {
    // Midlertidigt fordel deck i 7 kolonner
    Card* columns[7] = {NULL};
    Card* column_tails[7] = {NULL};
    int layout[7] = {1, 6, 7, 8, 9, 10, 11};

    for (int col = 0; col < 7; col++) {
        for (int i = 0; i < layout[col]; i++) {
            if (!head) break;

            Card* temp = head;
            head = head->next;
            temp->next = NULL;
            temp->face_up = 1;  // 👈 vis altid kortet!

            if (!columns[col]) {
                columns[col] = column_tails[col] = temp;
            } else {
                column_tails[col]->next = temp;
                column_tails[col] = temp;
            }
        }
    }

    // Udskriv kolonneoverskrifter
    printf("\nC1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    // Find største højde
    int max_height = 0;
    for (int i = 0; i < 7; i++) {
        int count = 0;
        Card* c = columns[i];
        while (c) {
            count++;
            c = c->next;
        }
        if (count > max_height) max_height = count;
    }

    // Udskriv række for række
    for (int row = 0; row < max_height; row++) {
        for (int col = 0; col < 7; col++) {
            Card* c = columns[col];
            for (int i = 0; i < row && c; i++) {
                c = c->next;
            }

            if (c) {
                char* s = card_to_string(c);  // viser AH, 3C osv.
                printf("%s\t", s);
                free(s);
            } else {
                printf("\t");
            }
        }
        printf("\n");
    }

    printf("\n");
}
