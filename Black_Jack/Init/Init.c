#include "Init.h"


void init(GameState * p_game_state){


    *p_game_state->curr_state=*p_game_state->next_state;
    *p_game_state->next_state=Betting;
    p_game_state->deck->head=NULL;
    p_game_state->player_hand->head=NULL;
    p_game_state->dealer_hand->head=NULL;
    initDeck(p_game_state);
    return;
    
}

void initDeck(GameState* p_game_state){
    Card * p_last={0};
    
    for ( uint8_t i=1 ; i<=RANK_NUMBER ; i++) {
        for ( uint8_t j=1 ; j<=SUIT_NUMBER ; j++) {
            if (i==1 && j==1){
                p_game_state->deck->head=cardNew(i,j);
                p_game_state->deck->list_length++;
                p_last=p_game_state->deck->head;
                continue;

            }
            
            p_last->next_card=cardNew(i,j);
            p_game_state->deck->list_length++;

            p_last=p_last->next_card;
        }

    }


}

Card * cardNew(uint8_t rank, uint8_t suit){
    Card * new_card=(Card*)malloc(sizeof(Card));
    if (NULL==new_card){
        printf("Allocation Problem!");
        free(new_card);
        exit(1); // check if this is right 
    }
    new_card->data=0u;
    new_card->data|=(rank_value[rank-1]<<4);
    new_card->data|=(suit_value[suit-1]);
    new_card->next_card=NULL;
    

    return new_card;

}

