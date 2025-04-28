#ifndef DECK_H
#define DECK_H

#include "card.h"

Card* load_deck(const char* filename);
void show_deck(Card* deck);
void interleave_shuffle(Card** head, int split);
void random_shuffle(Card** head);
void save_deck(Card* head, const char* filename);

#endif
