#include "Reset_Cards.h"

void resetCards(GameState* p_game_state) {
    char answer[1024]={0};
    char answer_final[4]={0};
    p_game_state->curr_state=p_game_state->next_state;
    sleep(RESET_CARDS_WAIT_SECONDS);
    printf("(Retrieving Cards to deck...)\n");
    retrieveCards(p_game_state->player_hand,p_game_state->dealer_hand,p_game_state->deck );
    if (p_game_state->cash<10){
        printf("You have less than 10$. Game is over!\n");
        *p_game_state->next_state=GameOver;
        return;
    }

    
    while(1){
        sleep(RESET_CARDS_WAIT_SECONDS);
        printf("Do you want to continue for another round? Type Yes/No\n");
        if (fgets(answer,4,stdin)!=NULL){
            clearInputBuffer(answer); // Clear the input buffer

            sscanf(answer,"%s", answer_final);
            if (strcmp(answer_final,"Yes")==0){
                *(p_game_state->next_state)=Betting;
                return;
            }
            else if (strcmp(answer_final,"No")==0){
               *(p_game_state->next_state)=GameOver;
                return;

            }
            else{
                printf("Please insert a valid input.\n");
                
            }

        }
        else{
            printf("Error in memory!\n");
            exit(1);
        }
    }
       
    
  
}
    


void retrieveCards(CardList* player_hand,CardList* dealer_hand, CardList* dec){
    Card * p_last_dec= dec->head;
    if (p_last_dec!=NULL){
        while(p_last_dec->next_card!=NULL){
            p_last_dec=p_last_dec->next_card;
            
        }
    }
    else{
        /*what todo?*/
    }

    p_last_dec=retrieveHand(p_last_dec,player_hand);
    p_last_dec=retrieveHand(p_last_dec,dealer_hand);
    dec->list_length=52;
    dealer_hand->list_length=0;
    player_hand->list_length=0;

}

Card* retrieveHand(Card * p_last_dec, CardList * hand){
    Card* p_curr_hand=hand->head;
    if (p_curr_hand!=NULL){
        p_last_dec->next_card=p_curr_hand;
        hand->head=NULL;
        p_last_dec=p_last_dec->next_card;
        while(p_last_dec->next_card!=NULL){
            p_last_dec=p_last_dec->next_card;
        }
        
        return p_last_dec;
    }
    printf("No cards to retrieve!\n"); 
    return p_curr_hand;

}

