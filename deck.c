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

//deck intitialization
    for(int i=0; i<4; i++){
        char current_suit = suits[i];
        for(int j=0; j<13; j++){
            deck_index = i*13+j;
            char* current_rank = ranks[j];
            struct card card;
            card.suit = current_suit;
            strcpy(card.rank, current_rank);
            deck_instance.list[deck_index] = card;
        }
    }

    if(deck_index != 51){
        return -1;
    }

//deck shuffling
//implement shuffling algorithm (Fisher yates algorithm)
    for(int x=0; x<52; x++){
        int y = (rand() % (52-x)) + x;
        struct card temp = deck_instance.list[x];
        deck_instance.list[x] = deck_instance.list[y];
        deck_instance.list[y] = temp;
    }

    return 0;
}


int deal_player_cards(struct player *target){
    while(target->hand_size < 7){
       struct card* card = next_card();
       if(card == NULL){
        return -1;
       }
       add_card(target, card); 
    }
    return 0;
}

struct card* next_card(){
    int top_index = deck_instance.top_card;
    if(top_index >=52){
        //deck is empty
        return NULL;
    }
    struct card* card;
    card = &deck_instance.list[top_index];
    deck_instance.top_card++;
    return card;
}

























