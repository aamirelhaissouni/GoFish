#include "player.h"
//#include <cstring>


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

int remove_card(struct player* target, struct card* old_card){
    struct hand* current_card = target->card_list;
    struct hand* previous_card = NULL;
    char* current_rank = current_card->top.rank;
    char current_suit = current_card->top.suit;
    if(current_card == NULL){
        //hand is already empty
        return -1;
    }
    while(current_suit != old_card->suit || strcmp(current_rank, old_card->rank) != 0){
        previous_card = current_card;
        current_card = current_card->next;
        if (current_card == NULL){
            //card not found
            return -1;
        }
    }
    if(previous_card != NULL){
        previous_card->next = current_card->next;
    }else{
        target->card_list = current_card->next; 
    }
    free(current_card);
    target->hand_size--;
    return 0;
}

/*
 * Function: check_add_book
 * ------------------------
 *  Check if a player has all 4 cards of the same rank.
 *  If so, remove those cards from the hand, and add the rank to the book.
 *  Returns after finding one matching set of 4, so should be called after adding each a new card.
 * 
 *  target: pointer to the player to check
 *  
 *  Return: a char that indicates the book that was added; return 0 if no book added.
 
char check_add_book(struct player *target){
    char suits[4] = {'C', 'D', 'H', 'S'};
    char* ranks[13] = {"2", "3", "4", "5", "6", "7", "8", "10", "J", "Q", "K"};
    struct hand* current_card = target->card_list;
    char* current_rank = current_card->top.rank;
    char current_suit = current_card->top.suit;
    
    if(current_card == NULL){
        //hand is empty
        return 0;
    }
    
    int count = 0;
    int i = 0;
    for(i; i<13; i++){
        char* target_rank = ranks[i];
        while(current_card != NULL){
            if(strcmp(current_rank, target_rank) == 0){
                count++;
            }
            current_card = current_card->next;
        }
        if(count == 4){
            //target_rank has all 4 cards so remove from hand and add to book

        }
    }
 

}
*/









