#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "deck.h"
#include "game.h"
#include "game.h"

int play_mode = 0;

// Funktioner
int parse_move(const char* input, int* src_col, char* rank, char* suit, char* dest_type, int* dest_num);

int main() {
    Card* deck = NULL;
    char input[100];

    printf("Welcome to Yukon!\n");

    while (1) {
        printf("INPUT > ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // fjerner newline

        if (strncmp(input, "LD", 2) == 0) {
            char* filename = input + 3;
            deck = load_deck(strlen(filename) > 0 ? filename : "cards.txt");

            if (deck) {
                printf("Message: OK\n");
            } else {
                printf("Message: Cannot load deck.\n");
            }
        } else if (strcmp(input, "SW") == 0) {
            if (deck) {
                show_deck(deck);
                printf("Message: OK\n");
            } else {
                printf("Message: No deck loaded.\n");
            }
        } else if (strncmp(input, "SI", 2) == 0) {
            int split = 26;
            if (strlen(input) > 2) {
                sscanf(input + 3, "%d", &split);
            }
            interleave_shuffle(&deck, split);
            printf("Message: OK (interleave shuffle)\n");
        } else if (strcmp(input, "SR") == 0) {
            random_shuffle(&deck);
            printf("Message: OK (random shuffle)\n");
        } else if (strncmp(input, "SD", 2) == 0) {
            char* filename = input + 3;
            save_deck(deck, strlen(filename) > 0 ? filename : "cards.txt");
        } else if (strcmp(input, "P") == 0) {
            if (!deck) {
                printf("Message: No deck loaded.\n");
                continue;
            }
            deal_to_columns(&deck);
            display_game();
            play_mode = 1;
            printf("Message: OK\n");
        } else if (strcmp(input, "QQ") == 0) {
            printf("Quitting...\n");
            break;
        } else if (strcmp(input, "Q") == 0) {
            if (play_mode) {
                clear_columns();
                play_mode = 0;
                printf("Message: Game aborted. Returning to startup mode.\n");
            } else {
                printf("Message: No game in progress.\n");
            }
        } else if (input[0] == 'C') {
            int src_col, dest_num;
            char rank, suit, dest_type;

            if (parse_move(input, &src_col, &rank, &suit, &dest_type, &dest_num)) {
                Card* moving_stack = cut_cards_from_column(src_col, rank, suit);

                if (moving_stack) {
                    if (dest_type == 'C') {
                        Card* dest_top = columns[dest_num - 1].top;

                        if (is_valid_move(moving_stack, dest_top)) {
                            add_cards_to_column(dest_num, moving_stack);
                            printf("Message: Move successful.\n");
                            display_game();
                        } else {
                            printf("Message: Invalid move (illegal move according to rules).\n");
                            add_cards_to_column(src_col, moving_stack);
                        }
                    } else if (dest_type == 'F') {
                        Card* foundation_top = foundations[dest_num - 1].top;

                        if (is_valid_foundation_move(moving_stack, foundation_top)) {
                            add_card_to_foundation(dest_num, moving_stack);
                            printf("Message: Moved to foundation.\n");
                            display_game();
                        } else {
                            printf("Message: Invalid move to foundation.\n");
                            add_cards_to_column(src_col, moving_stack);
                        }
                    } else {
                        printf("Message: Invalid destination type.\n");
                        add_cards_to_column(src_col, moving_stack);
                    }
                } else {
                    printf("Message: Card not found or not movable.\n");
                }
            } else {
                printf("Message: Invalid move format.\n");
            }
        } else {
            printf("Message: Unknown command.\n");
        }
    }

    free_deck(deck);
    return 0;
}

int parse_move(const char* input, int* src_col, char* rank, char* suit, char* dest_type, int* dest_num) {
    if (input[0] != 'C') return 0;
    if (!isdigit(input[1])) return 0;

    *src_col = input[1] - '0';

    if (input[2] != ':') return 0;
    *rank = input[3];
    *suit = input[4];

    if (input[5] != '-' || input[6] != '>') return 0;
    *dest_type = input[7];

    if (!isdigit(input[8])) return 0;
    *dest_num = input[8] - '0';

    return 1;
}
