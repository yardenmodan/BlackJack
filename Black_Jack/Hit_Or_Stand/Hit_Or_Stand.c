#include "Hit_Or_Stand.h"





unsigned int hitOrStand( GameState* p_game_state) {
    *p_game_state->curr_state=*p_game_state->next_state;
    hit_or_stand decision_int;
    char buff[MAX_BUFF_SIZE]={0};
    char decision[MAX_BUFF_SIZE]={0};

    unsigned int calc_value=calcValue(p_game_state->player_hand);
    sleep(HIT_OR_STAND_WAIT_CHECK);
    printf("Your current score is %u.\n",calc_value);

    if (calc_value==BLACK_JACK){
        
        *p_game_state->next_state=DealerDraw;
        return calc_value;
    }
    else if (calc_value>BLACK_JACK){
        sleep(HIT_OR_STAND_WAIT_CHECK);

        printf("Bust!\n");
        p_game_state->pot=0;
        *p_game_state->next_state=ResetCards;
        return calc_value;

    }
    else{
        sleep(HIT_OR_STAND_WAIT_CHECK);

        while(1){
            memset(buff,0,sizeof(buff));
            memset(decision,0,sizeof(decision));
            printf("Player: please type Hit/Stand:\n");
            if (fgets(buff,sizeof(buff),stdin)!=NULL){
                clearInputBuffer(buff); // Clear the input buffer

                sscanf(buff,"%s", decision);
                
                if (strcmp(decision,"Hit")==0){
                    decision_int=HIT;
                    
                    
                    break;
                }
                else if (strcmp(decision,"Stand")==0){
                    decision_int=STAND;
                    break;
                }
                else{
                    printf("Invlid input!\n");
                    continue;
                }
                
            }
            else{
                printf("Error of memory!\n");
                exit(1);    
            }
            
        }

        if (decision_int==STAND){
            *p_game_state->next_state=DealerDraw;
            return calc_value;
        }
        else{

            insertCard(p_game_state->deck, p_game_state->player_hand);
            printNew(p_game_state->player_hand);
            *p_game_state->next_state=HitOrStand;
            return calc_value;
        }
    }    
}
