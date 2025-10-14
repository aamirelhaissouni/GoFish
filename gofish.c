#include <stdio.h>
#include "deck.h"
#include "player.h"

int main(int args, char* argv[]) 
{
    fprintf(stdout, "Put your code here.");
    
    //test shuffle()
    shuffle();
    fprintf(stdout, "Deck initialized!");
    //test deal_player cards()
    struct player* user_p = &user;
    deal_player_cards(user_p);
    fprintf(stdout, "Dealt cards to player!");  
    //test add_card() and next card()
    struct card* new_card = next_card();
    add_card(user_p, new_card);
    fprintf(stdout, "Successfully added new card to player from deck");
    
}
