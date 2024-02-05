#ifndef _HIT_OR_STAND_H
#define _HIT_OR_STAND_H


#include "../Black_Jack.h"

typedef enum hit_or_stand{
    HIT=0,
    STAND=1
}hit_or_stand;

unsigned int hitOrStand( GameState* p_game_state);

#endif