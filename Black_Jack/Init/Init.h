#ifndef _INIT_H
#define _INIT_H
#include "../Black_Jack.h"

Card * cardNew(uint8_t rank, uint8_t suit);
void initDeck(GameState* p_game_state);
void init(GameState * p_game_state);

#endif