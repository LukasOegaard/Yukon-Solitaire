#include "game.h"
#include <stdio.h>
#include <stdlib.h>

Pile columns[COLUMN_COUNT];
Pile foundations[FOUNDATION_COUNT];

void deal_to_columns(Card** deck) {
    int layout[COLUMN_COUNT] = {1, 6, 7, 8, 9, 10, 11};

    for (int i = 0; i < COLUMN_COUNT; i++) {
        Card* prev = NULL;

        for (int j = 0; j < layout[i]; j++) {
            if (*deck == NULL) return;

            Card* current = *deck;
            *deck = current->next;
            current->next = NULL;

            if (prev == NULL) {
                columns[i].top = current;
            } else {
                prev->next = current;
            }

            prev = current;
        }

        // Gør nederste kort synligt
        Card* c = columns[i].top;
        while (c->next) {
            c = c->next;
        }
        if (c) c->face_up = 1;
    }
}

void display_game(void) {
    printf("\nC1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    // Find den højeste kolonne (så vi ved hvor mange rækker vi skal vise)
    int max_height = 0;
    for (int i = 0; i < COLUMN_COUNT; i++) {
        int count = 0;
        Card* c = columns[i].top;
        while (c) {
            count++;
            c = c->next;
        }
        if (count > max_height) {
            max_height = count;
        }
    }

    // Print kortene række for række
    for (int row = 0; row < max_height; row++) {
        for (int col = 0; col < COLUMN_COUNT; col++) {
            Card* c = columns[col].top;
            for (int i = 0; i < row && c; i++) {
                c = c->next;
            }

            if (c) {
                char* s = card_to_string(c);
                printf("%s\t", s);
                free(s);
            } else {
                printf("\t");
            }
        }
        printf("\n");
    }

    // Vis foundations (bare tomme placeholders for nu)
    for (int i = 0; i < FOUNDATION_COUNT; i++) {
        printf("[] F%d\t", i + 1);
    }
    printf("\n\n");
}
