#include "Black_Jack.h"
#include "./Betting/Betting.h"
#include "./BJ_check/BJ_check.h"
#include "./Dealer_Draw/Dealer_Draw.h"
#include "./Game_Over/Game_Over.h"
#include "./Hit_Or_Stand/Hit_Or_Stand.h"
#include "./Init/Init.h"
#include "./Init_Deal/Init_Deal.h"
#include "./Reset_Cards/Reset_Cards.h"


const uint8_t suit_value[SUIT_NUMBER]={1u,2u,4u,8u};
const uint8_t rank_value[RANK_NUMBER]={1u,2u,3u,4u,5u,6u,7u,8u,9u,10u,11u,12u,13u};
const char  rank_by_value[CARD_NUMBER][MAX_RANK_NAME_LEN+1]=
{
    ACE_COLOR ACE_SYMBOL COLOR_RESET,
    TWO_COLOR "2" COLOR_RESET,
    THREE_COLOR "3" COLOR_RESET,
    FOUR_COLOR "4" COLOR_RESET,
    FIVE_COLOR "5" COLOR_RESET,
    SIX_COLOR "6" COLOR_RESET,
    SEVEN_COLOR "7" COLOR_RESET,
    EIGHT_COLOR "8" COLOR_RESET,
    NINE_COLOR "9" COLOR_RESET,
    TEN_COLOR "10" COLOR_RESET,
    JACK_COLOR JACK_SYMBOL COLOR_RESET,
    QUEEN_COLOR QUEEN_SYMBOL COLOR_RESET,
    KING_COLOR KING_SYMBOL COLOR_RESET
    };
const char suit_by_value[SUIT_NUMBER][MAX_SUIT_NAME_LEN+1]=
{
    HEARTS_COLOR HEARTS_SYMBOL COLOR_RESET,
    CLUBS_COLOR CLUBS_SYMBOL COLOR_RESET,
    DIAMONDS_COLOR DIAMONDS_SYMBOL COLOR_RESET,
    SPADES_COLOR SPADES_SYMBOL COLOR_RESET
};

void startBlackJack(void) {
    printf(DARK_GREEN_COLOR "\t\t\t$$$$$$$$$$$$$$$$$$$$$$$$ Welcome to Blackjack $$$$$$$$$$$$$$$$$$$$$$$$ \n\n\n" COLOR_RESET);
    State curr_state={0};
    State next_state={0};

    CardList deck={0};
    CardList player_hand={0};
    CardList dealer_hand={0};

    GameState game_state={0}; 
    unsigned int calc_value=0;
    GameState* p_game_state= initGameState(&deck, &player_hand,&dealer_hand,&curr_state,&next_state,&game_state);
   
    while(true){
        switch(*(p_game_state->next_state))
        {               
            case (Init):
                init(p_game_state);
                break;
            case (Betting):
                betting(p_game_state);
                break;
            case (InitDeal):
                initDeal(p_game_state);
                break;
            case (BJCheck):
                calc_value=bjCheck(p_game_state);
                break;
            case (HitOrStand):
                calc_value=hitOrStand(p_game_state);
                break;
            case (DealerDraw):
                dealerDraw(p_game_state, calc_value);
                break;
            case (ResetCards):
                resetCards(p_game_state);
                break;
            case (GameOver):
                gameOver(p_game_state);
                break;
            case (Terminate):
                return;
                break;


        }
    }
    return;
}





char* getRank(Card* card){
    uint8_t val=card->data>>4;
    return rank_by_value[val-1];
 
}

char* getSuit(Card* card){
    uint8_t val=(card->data)&0b00001111;
    uint8_t shifts=0;
    while (val!=0b00000001){
        val=val>>1;
        shifts++;
    }
    return suit_by_value[shifts];
    
}


GameState* initGameState(CardList *deck, CardList* player_hand, CardList* dealer_hand,State* curr_state, State* next_state,GameState* game_state){

    deck->head=NULL;
    player_hand->head=NULL;
    dealer_hand->head=NULL;
    *curr_state=Init;
    *next_state=Init;
    game_state->cash=1000;
    game_state->pot=0;
    game_state->next_state=next_state;
    game_state->curr_state=curr_state;
    game_state->dealer_hand=dealer_hand;
    game_state->player_hand=player_hand;
    game_state->deck=deck;
    return game_state;
}

unsigned int calcValue(CardList * list){
    unsigned int aces=0;
    unsigned int value=0;
    uint8_t curr_val=0;
    Card* card=list->head;
    for(int i=0; i<(int)list->list_length;i++){
        curr_val=min(10,(card->data)>>4);
        if (curr_val==1){
            aces++;
            
        }
       
        value+=curr_val;

        card=card->next_card;
    }
    while (value+10 <=21 && aces>0){
        value+=10;
        aces--;
    }
    return value;
 

 
}

uint8_t min(uint8_t a, uint8_t b){
    uint8_t min_num=a < b ? a:  b;
    return min_num;
}

void insertCard(CardList * dec, CardList *hand){
    if (dec->list_length>0){
        Card * new_card=drawCard(dec);
        if (hand->list_length==0){
            hand->head=new_card;
            
        }
        else{
            Card * ptr =hand->head;
            for (int iter=0; iter<(int)(hand->list_length-1);iter++){
                ptr=ptr->next_card;
            }
            ptr->next_card=new_card;

        }
        hand->list_length++;
        return;
    }
    printf("No cards left in deck!\n");
    return;
}
    

Card * drawCard(CardList *dec) {
    srand(time(NULL));

    if (dec->head == NULL || dec->list_length == 0) {
        // Empty deck
        return NULL;
    }

    uint8_t chosen_index = rand() % (dec->list_length);

    Card *chosen_card = dec->head;
    Card *prev_card = NULL;

    for (int iter = 0; iter < chosen_index; iter++) {
        prev_card = chosen_card;
        chosen_card = chosen_card->next_card;

        if (chosen_card == NULL) {
            // Invalid index reached
            return NULL;
        }
    }

    // Removing chosen card from the list
    if (prev_card != NULL) {
        prev_card->next_card = chosen_card->next_card;
    } else {
        // Updating head if the first card is chosen
        dec->head = chosen_card->next_card;
    }

    chosen_card->next_card = NULL; // Separate the chosen card from the list
    dec->list_length--;

    return chosen_card;
}

void printNew(CardList * player_card){
    Card * card=player_card->head;
    while(card->next_card!=NULL){
        card=card->next_card;
    }
    printf("New drawn card is: %s of %s\n", getRank(card), getSuit(card));
    return;
}


void clearInputBuffer(char* buffer) {
    char *p=0;
   if (p=strchr(buffer, '\n')){//check exist newline
        *p = 0;
    } else {
        scanf("%*[^\n]");scanf("%*c");//clear upto newline
    }
}