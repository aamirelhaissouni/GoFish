#include "player.h"

/*
 * Instance Variables: user, computer   
 * ----------------------------------
 *  
 *  We only support 2 users: a human and a computer
 */
struct player user;
struct player computer;

int add_card(struct player* target, struct card* new_card){
    //initialize new hand node
    struct hand* temp;
    temp = (struct hand*)malloc(sizeof(struct hand));
    if(temp == NULL){
        return -1;
    }
    temp->top = *new_card;
    temp->next = NULL;
    
    //insert new card/hand node into deck
    if(target->card_list == NULL){
        //player has no cards, new card is top of list
        target->card_list = temp;
    }else{
        struct hand* current = target->card_list;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = temp;
    }
    target->hand_size++;
   return 0;
}

/*
 * Function: remove_card
 * ---------------------
 *  Remove a card from the player's hand. 
 *
 *  target: the target player
 *  old_card: pointer to the old card to remove
 *
 *  returns: return 0 if no error, non-zero otherwise
 */

int remove_card(struct player* target, struct card* old_card){
    struct hand* current_card = target->card_list;
    struct hand* previous_card = NULL;
    char current_rank = current_card->top.rank;
    char current_suit = current_card->top.suit;
    if(current_card == NULL){
        //hand is already empty
        return -1;
    }
    while(current_card !=){
        previous_card = current_card;
        current_card = current_card->next;
        if (current_card == NULL){
            //card not found
            return -1;
        }
    if(previous_card != NULL){
        previous_card->next = current_card->next;
    }else{
        target->card_list = current_card->next; 
    }
    }
}









