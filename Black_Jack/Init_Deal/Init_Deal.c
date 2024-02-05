
#include "Init_Deal.h"

void initDeal(GameState* p_game_state) {
    *p_game_state->curr_state=*p_game_state->next_state;
    *p_game_state->next_state=BJCheck;
    for (int iter=0;iter<2;iter++){
        insertCard(p_game_state->deck,p_game_state->dealer_hand);
        insertCard(p_game_state->deck,p_game_state->player_hand);
    }
    showCards(p_game_state->player_hand,p_game_state->dealer_hand);
}
    

void showCards(CardList * player_hand, CardList * dealer_hand){
    printf("(Player and dealer are drawing cards...)\n");
    sleep(INIT_DEAL_WAIT_SECONDS);
    printf("Dealer: %s of %s, ????????\n", getRank(dealer_hand->head),getSuit(dealer_hand->head));
    printf("Player: %s of %s, %s of %s\n", getRank(player_hand->head), getSuit(player_hand->head),getRank(player_hand->head->next_card),\
    getSuit(player_hand->head->next_card));
}


