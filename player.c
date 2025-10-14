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
