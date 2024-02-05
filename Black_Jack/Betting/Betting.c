#include "Betting.h"




void betting(GameState* p_game_state){
    uint32_t add_to_pot=0;
    *(p_game_state->curr_state)=*(p_game_state->next_state);
    sleep(BETTING_WAIT_SECONDS);
    printf("Player's cash: %d, Player's pot: %d\n", p_game_state->cash, p_game_state->pot);
    if (p_game_state->pot==0 && p_game_state->cash<10){
        *(p_game_state->next_state)=GameOver;
        return;
    }
    else{
        
        add_to_pot=getAmountToAdd(p_game_state->cash,p_game_state->pot);
        p_game_state->cash-=add_to_pot;
        p_game_state->pot+=add_to_pot;
        *(p_game_state->next_state)=InitDeal;
        return;
    }
}


uint32_t getAmountToAdd(uint32_t cash, uint32_t pot) {

    int additional_bet;
    char buffer[MAX_BUFF_SIZE]; 
    
    while (1) {
        sleep(BETTING_WAIT_SECONDS);
        memset(buffer,0,sizeof(buffer));

        printf("How much would you like to add to the bet?\n" );

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            clearInputBuffer(buffer); // Clear the input buffer

            if (sscanf(buffer, "%d", &additional_bet)!=1){
                printf("Please enter a valid number!\n");
            }
            else if (additional_bet%10!=0) {
                printf("Please enter a valid bet amount in increments of 10 or 0.\n");
            }
            else if (additional_bet>(int)cash){
                printf("Please enter a valid bet amount less or equal to cash.\n");

            }
            else if  (additional_bet<0 || (additional_bet==0 && pot==0)){
                printf("Please enter a valid bet amount greater than zero.\n");
            }
            else{
                break;
            }
            
        
        }else{
            printf("Error reading input.\n");
            exit(1);
        }
        
        
        
    }
    // Clear input buffer
   
    return (uint32_t)additional_bet;
}
