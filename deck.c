#include "deck.h"
#include <string.h>

/*
 * Variable: deck_instance
 * -----------------------
 *  
 * Go Fish uses a single deck
 */
struct deck deck_instance;

int shuffle(){
    char suits[4] = {'C', 'D', 'H', 'S'};
    char* ranks[13] = {"2", "3", "4", "5", "6", "7", "8",
    "9", "10", "J", "K", "A"};

    int deck_index = 0;

    deck_instance.top_card = 0;

    for(int i=0; i<4; i++){
        char current_suit = suits[i];
        for(int j=0; j<13; j++){
            int deck_index = i*13+j;
            char* current_rank = ranks[j];
            struct card card;
            card.suit = current_suit;
            strcpy(card.rank, current_rank);
            deck_instance.list[deck_index] = card;
        }
    }
    if(deck_index !=51){
        return -1;
    }else{
        return 0;
    }
}

int deal_player_cards(struct player *target){
   return 0; 
}

struct card* next_card(){
    int top_index = deck_instance.top_card;
    if(top_index >=52){
        //deck is empty
        return NULL;
    }
    struct card* cardy;
    cardy = &deck_instance.list[top_index];
    deck_instance.top_card++;
    return cardy;
}

























