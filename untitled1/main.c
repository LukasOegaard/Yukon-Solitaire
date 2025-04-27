#include <stdio.h>
#include <string.h>
#include "deck.c"   // midlertidigt for demo
#include "card.c"
#include "game.h"


int main() {
    Card* deck = NULL;
    char input[100];

    printf("Welcome to Yukon!\n");

    while (1) {
        printf("INPUT > ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // fjern newline

        if (strncmp(input, "LD", 2) == 0) {
            char* filename = input + 3;
            deck = load_deck(strlen(filename) > 0 ? filename : "default.txt");
        } else if (strcmp(input, "SW") == 0) {
            if (deck) {
                show_deck(deck);
                printf("Message: OK\n");
            } else {
                printf("Message: No deck loaded.\n");
            }
        } else if (strcmp(input, "QQ") == 0) {
            printf("Quitting...\n");
            break;
        }
        else if (strncmp(input, "SI", 2) == 0) {
            if (!deck) {
                printf("Message: No deck loaded.\n");
                continue;
            }

            int split = 26; // default split
            if (strlen(input) > 2) {
                sscanf(input + 3, "%d", &split);
            }

            interleave_shuffle(&deck, split);
            printf("Message: OK (interleave shuffle)\n");
        }
        else if (strcmp(input, "SR") == 0) {
            if (!deck) {
                printf("Message: No deck loaded.\n");
                continue;
            }

            random_shuffle(&deck);
            printf("Message: OK (random shuffle)\n");
        }
        else if (strncmp(input, "SD", 2) == 0) {
            char* filename = input + 3;
            save_deck(deck, strlen(filename) > 0 ? filename : "cards.txt");
        }
        else if (strcmp(input, "P") == 0) {
            if (!deck) {
                printf("Message: No deck loaded.\n");
                continue;
            }
            deal_to_columns(&deck);
            display_game();
            printf("Message: OK\n");
        } else {
            printf("Message: Unknown command.\n");
        }

    }

    free_deck(deck);
    return 0;
}

