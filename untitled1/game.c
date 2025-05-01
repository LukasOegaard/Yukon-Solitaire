#include "game.h"
#include <stdio.h>

Pile columns[COLUMN_COUNT];
Pile foundations[FOUNDATION_COUNT];

void deal_to_columns(Card** deck) {
    int layout[] = {1, 6, 7, 8, 9, 10, 11};  // antal kort per kolonne

    for (int i = 0; i < COLUMN_COUNT; i++) {
        columns[i].top = NULL;
        Card* prev = NULL;

        for (int j = 0; j < layout[i]; j++) {
            if (!*deck) return;

            Card* current = *deck;
            *deck = current->next;
            current->next = NULL;

            // Alle kort er face down indtil sidste
            current->face_up = (j == layout[i] - 1) ? 1 : 0;

            if (!columns[i].top) {
                columns[i].top = current;
            } else {
                prev->next = current;
            }

            prev = current;
        }
    }
}


void display_game(void) {
    printf("\nC1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    int max_height = 0;
    for (int i = 0; i < COLUMN_COUNT; i++) {
        int h = 0;
        Card* c = columns[i].top;
        while (c) {
            h++;
            c = c->next;
        }
        if (h > max_height) max_height = h;
    }

    for (int row = 0; row < max_height; row++) {
        for (int col = 0; col < COLUMN_COUNT; col++) {
            Card* c = columns[col].top;
            for (int i = 0; i < row && c; i++) {
                c = c->next;
            }

            if (c) {
                char* str = card_to_string(c);
                printf("%s\t", str);
                free(str);
            } else {
                printf("\t");
            }
        }
        printf("\n");
    }

    printf("\n");
}


void clear_columns(void) {
    for (int i = 0; i < COLUMN_COUNT; i++) {
        free_deck(columns[i].top);
        columns[i].top = NULL;
    }
    for (int i = 0; i < FOUNDATION_COUNT; i++) {
        free_deck(foundations[i].top);
        foundations[i].top = NULL;
    }
}

Card* cut_cards_from_column(int src_col, char rank, char suit) {
    if (src_col < 1 || src_col > COLUMN_COUNT) return NULL;

    Card* current = columns[src_col - 1].top;
    Card* previous = NULL;

    while (current) {
        if (current->face_up && current->rank == rank && current->suit == suit) {
            if (previous) {
                previous->next = NULL;
                if (!previous->face_up) {
                    previous->face_up = 1;
                }
            } else {
                columns[src_col - 1].top = NULL;
            }
            return current;
        }
        previous = current;
        current = current->next;
    }

    return NULL;
}

void add_cards_to_column(int dst_col, Card* stack) {
    if (dst_col < 1 || dst_col > COLUMN_COUNT || !stack) return;

    Card* top = columns[dst_col - 1].top;

    if (!top) {
        columns[dst_col - 1].top = stack;
    } else {
        Card* current = top;
        while (current->next) {
            current = current->next;
        }
        current->next = stack;
    }
}

int is_valid_move(Card* moving_card, Card* destination_card) {
    if (!destination_card) {
        return rank_to_value(moving_card->rank) == 13;
    }

    int moving_value = rank_to_value(moving_card->rank);
    int dest_value = rank_to_value(destination_card->rank);

    int color_different = is_red(moving_card->suit) != is_red(destination_card->suit);
    int correct_rank = (moving_value + 1 == dest_value);

    return color_different && correct_rank;
}

int is_valid_foundation_move(Card* moving_card, Card* foundation_top) {
    if (!moving_card) return 0;

    int moving_value = rank_to_value(moving_card->rank);

    if (!foundation_top) {
        return (moving_value == 1);
    }

    int foundation_value = rank_to_value(foundation_top->rank);

    return (moving_value == foundation_value + 1) && (moving_card->suit == foundation_top->suit);
}

void add_card_to_foundation(int foundation_num, Card* card) {
    if (foundation_num < 1 || foundation_num > FOUNDATION_COUNT || !card) return;

    card->next = foundations[foundation_num - 1].top;
    foundations[foundation_num - 1].top = card;
}

int is_red(Suit suit) {
    return (suit == HEARTS || suit == DIAMONDS);
}

int rank_to_value(char rank) {
    if (rank >= '2' && rank <= '9') return rank - '0';
    switch (rank) {
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        case 'A': return 1;
        default: return 0;
    }
}
