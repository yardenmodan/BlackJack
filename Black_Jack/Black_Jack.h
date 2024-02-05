#ifndef _BJ_H
#define _BJ_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <unistd.h>

#define DARK_GREEN_COLOR   "\x1b[0;32m"         // Darker shade of green
#define ACE_COLOR          "\x1b[33m"        // Gold/Yellow for Ace
#define TWO_COLOR          "\x1b[32m"        // Green for 2
#define THREE_COLOR        "\x1b[34m"      // Blue for 3
#define FOUR_COLOR         "\x1b[35m"       // Purple for 4
#define FIVE_COLOR         "\x1b[33m"       // Orange for 5
#define SIX_COLOR          "\x1b[36m"        // Cyan for 6
#define SEVEN_COLOR        "\x1b[35m"      // Magenta for 7
#define EIGHT_COLOR        "\x1b[36m"      // Teal for 8
#define NINE_COLOR         "\x1b[31m"       // Dark Red for 9
#define TEN_COLOR          "\x1b[33m"        // Dark Yellow for 10
#define JACK_COLOR         "\x1b[1;31m"     // Bright Red for Jack
#define QUEEN_COLOR        "\x1b[1;32m"    // Bright Green for Queen
#define KING_COLOR         "\x1b[1;34m"     // Bright Blue for King
#define CLUBS_COLOR        "\x1b[1;30m"    // Bright black or dark gray for clubs
#define SPADES_COLOR       "\x1b[1;30m"   // Bright black or dark gray for spades (same as clubs)
#define DIAMONDS_COLOR     "\x1b[1;31m"
#define HEARTS_COLOR       "\x1b[1;31m"
#define COLOR_RESET        "\x1b[0m"
#define SPADES_SYMBOL      "\u2660"
#define CLUBS_SYMBOL       "\u2663"
#define HEARTS_SYMBOL      "\u2665"
#define DIAMONDS_SYMBOL    "\u2666"
#define JACK_SYMBOL        "J"
#define QUEEN_SYMBOL       "Q"
#define KING_SYMBOL        "K"
#define ACE_SYMBOL         "A"

#define MAX_BUFF_SIZE 1024

#define DEALER_DRAW_WAIT_CHECK 1
#define RESET_CARDS_WAIT_SECONDS 1
#define INIT_DEAL_WAIT_SECONDS 2.5
#define BETTING_WAIT_SECONDS 1
#define HIT_OR_STAND_WAIT_CHECK 1
#define BJCHECK_WAIT_SECONDS 1
#define GAME_OVER_WAIT_SECONDS 2

#define BLACK_JACK 21
#define INIT_DEAL_CARDS_NUMBER 2
#define CARD_NUMBER 13
#define MAX_RANK_NAME_LEN 100
#define SUIT_NUMBER 4
#define MAX_SUIT_NAME_LEN 80
#define RANK_NUMBER 13


typedef struct Card {
    uint8_t data;
    struct Card* next_card;
} Card;

typedef struct CardList {
    Card *head;
    size_t list_length;
} CardList;

typedef enum State {
    Init,
    Betting,
    InitDeal,
    BJCheck,
    HitOrStand,
    DealerDraw,
    ResetCards,
    GameOver,
    Terminate
} State;

typedef struct GameState {
    State * curr_state;
    State * next_state;
    CardList * dealer_hand;
    CardList * player_hand;
    CardList * deck;
    uint32_t pot;
    uint32_t cash;
} GameState;

GameState* initGameState(CardList *deck, CardList *player_hand, CardList* dealer_hand,State* curr_state, State* next_state,GameState* game_state);
void    startBlackJack(void);
char* getRank(Card* card);
char* getSuit(Card* card);
uint8_t min(uint8_t a, uint8_t b);
unsigned int calcValue(CardList * list);
void insertCard(CardList * dec, CardList *hand);
Card * drawCard(CardList *dec) ;
void printNew(CardList * player_card);
uint8_t min(uint8_t a, uint8_t b);
void clearInputBuffer(char* buffer) ;
extern const uint8_t suit_value[SUIT_NUMBER];
extern const uint8_t rank_value[RANK_NUMBER];
extern const char  rank_by_value[CARD_NUMBER][MAX_RANK_NAME_LEN+1];
extern const char  suit_by_value[SUIT_NUMBER][MAX_SUIT_NAME_LEN+1];



#endif 

