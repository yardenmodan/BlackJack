
#include "BJ_check.h"






unsigned int bjCheck(GameState* p_game_state) {
    *(p_game_state->curr_state)=*(p_game_state->next_state);
    unsigned int calc_value=calcValue(p_game_state->player_hand);
    if (calc_value==BLACK_JACK){
        sleep(BJCHECK_WAIT_SECONDS);
        printf("Black Jack!!\n");
        p_game_state->cash+=2.5*p_game_state->pot;
        p_game_state->pot=0;
        *(p_game_state->next_state)=ResetCards;
        return calc_value;
    }
    

    
    *p_game_state->next_state=HitOrStand;
    return calc_value;
        
    
}


