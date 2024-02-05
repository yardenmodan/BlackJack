#ifndef _RESET_CARDS_H
#define _RESET_CARDS_H

#include "../Black_Jack.h"

void resetCards(GameState* p_game_state);
void retrieveCards(CardList* player_hand,CardList* dealer_hand, CardList* dec);
Card* retrieveHand(Card * p_last_dec, CardList * hand);

#endif



