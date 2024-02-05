#include "Dealer_Draw.h"


void dealerDraw( GameState* p_game_state, unsigned int player_score) {
    sleep(DEALER_DRAW_WAIT_CHECK);
    printDealerCards(p_game_state->dealer_hand);
    *p_game_state->curr_state=*p_game_state->next_state;
   * p_game_state->next_state=ResetCards;

    unsigned int dealer_score=0;
    while((dealer_score=calcValue(p_game_state->dealer_hand))<17){
        if (dealer_score<=player_score){
            insertCard(p_game_state->deck,p_game_state->dealer_hand);
            printNew(p_game_state->dealer_hand);
        }
    
        else{
            sleep(DEALER_DRAW_WAIT_CHECK);
            printf("Dealer wins!\n");
            p_game_state->pot=0;
            return;
        }


        
       
    }
    
    sleep(DEALER_DRAW_WAIT_CHECK);

    if (dealer_score>BLACK_JACK){
        printf("Dealer bust!\n");
        p_game_state->cash+=(p_game_state->pot)*2;
        p_game_state->pot=0;
        return;

    }
    else if (dealer_score>player_score){
        printf("You lost!\n");
        p_game_state->pot=0;
        return;
    }
    else if (dealer_score==player_score){
        printf("Tie!\n");
        return;

    }
    else{ 
        printf("You won!\n");
        p_game_state->cash+=(p_game_state->pot)*2;
        p_game_state->pot=0;
        return;
    }
   
}




void printDealerCards(CardList * dealer_hand){
    Card* dealer_card=0;
    if (dealer_hand->head!=NULL){
        printf("Dealer's cards: ");

        dealer_card=dealer_hand->head;
        while(dealer_card->next_card!=NULL){
            printf("%s of %s, ", getRank(dealer_card),getSuit(dealer_card));
            dealer_card=dealer_card->next_card;
        


        }
        printf("%s of %s\n", getRank(dealer_card),getSuit(dealer_card));
        return;
    }
    printf("No cards in dealer's hand!\n");
    return;

}


