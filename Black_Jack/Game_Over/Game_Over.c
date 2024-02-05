#include "Game_Over.h"




void gameOver(GameState* p_game_state) {
    *p_game_state->curr_state=*p_game_state->next_state;
   * p_game_state->next_state=Terminate;
    freeMemory(p_game_state->deck);
    printf("Goodbye!");
    sleep(GAME_OVER_WAIT_SECONDS);
    return;
}

void freeMemory(CardList* deck_list){
    Card* current_card=deck_list->head;
    Card* card_next={0};
    if (current_card!=NULL){
        while (current_card->next_card!=NULL){
            card_next=current_card->next_card;
            free(current_card);
            current_card=card_next;
        }
        free(current_card);
    }
    else{
        return;
    }

}
