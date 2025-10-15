#include "player.h"
#include <stdio.h>
//#include <cstring>

char suits[4] = {'C', 'D', 'H', 'S'};
char* ranks[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};

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

    if(current_card == NULL){
        return -1;
    } 

    while(current_card->top.suit != old_card->suit || strcmp(current_card->top.rank, old_card->rank) != 0){
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
*/
 
char check_add_book(struct player *target){
    struct hand* current_card = target->card_list;

    if(current_card == NULL){
        //hand is empty
        return 0;
    }

    for(int i = 0; i<13; i++){
        int count = 0;
        current_card = target->card_list;
        char* target_rank = ranks[i];
        while(current_card != NULL){
            if(strcmp(current_card->top.rank, target_rank) == 0){
                count++;
            }
            current_card = current_card->next;
        }
        if(count == 4){
            //target_rank has all 4 cards so remove from hand and add to book
            strcat(target->book, target_rank);

            //remove the cards
            for(int x = 0; x<4; x++){
                struct card cardy;
                cardy.suit = suits[x];
                strcpy(cardy.rank, target_rank);
                remove_card(target, &cardy);
            }
            return target_rank[0];
        }
    }
    return 0;
}

int search(struct player* target, char rank){
    struct hand* current_card = target->card_list;

    if(current_card == NULL){
        //empty hand
        return 0;
    }
    while(current_card != NULL){
        if(current_card->top.rank[0] == rank){
            return 1;
        }
        current_card = current_card->next;
    }
    return 0;
}

int transfer_cards(struct player* src, struct player* dest, char rank){
    struct hand* source = src->card_list;
    struct card* transfer_array[4]; //max amount possible is 4 for each rank

    if(source == NULL){
        //players hand is empty
        return 0;
    }

    if(search(src, rank) == 0){
        //player does not have any cards of that rank
        return 0;
    }

    int count = 0;
    while(source != NULL && count < 4){
        if(source->top.rank[0] == rank){
            transfer_array[count] = &source->top;
            count++;
        }
        source = source->next;
    }

    for(int i = 0; i<count; i++){
       if(add_card(dest, transfer_array[i]) !=0){
        return -1;
       }
       if(remove_card(src, transfer_array[i]) !=0){
        return -1;
       }
   }
 
    return count;
}

int game_over(struct player* target){
    int count = 0;
    for(int i = 0; i<7; i++){
        if(target->book[i] !=0){
            count++;
        }
    }
    if(count == 7){
        return 1;
    }
    return 0;
}

int reset_player(struct player* target){
    //reinitialize book first
    for(int i = 0; i<7; i++){
        target->book[i] = 0;
    }

    struct hand* current_card = target->card_list;
    if(current_card == NULL){
        //hand already empty no need for reset
        return 0;
    }

    while(current_card != NULL){
        struct hand* temp = current_card;
        current_card = current_card->next;
        free(temp);
    }

    target->card_list = NULL;
    target->hand_size = 0;

    if(target->card_list != NULL || target->hand_size !=0){
        return -1;
    }
    return 0;
}

char computer_play(struct player* target){
    if(target->card_list == NULL){
        return 0;
    }

    int count = 0;
    char computer_ranks[13];    
    struct hand* current = target->card_list;

    while(current != NULL){
        char rank = current->top.rank[0];
        int found = 0;
        for(int i = 0; i<count; i++){
            if(rank == computer_ranks[i]){
                found = 1;
                break;
            }
        }
        if(found != 1){
            computer_ranks[count] = rank;
            count++;
        }
        current = current->next;
    }
    int rand_index = rand() % count;
    return computer_ranks[rand_index];
}

char user_play(struct player* target){
    char rank;

    while(1){
        printf("Enter what rank you would like to get (one char please): ");

        char input[100];
        if(fgets(input, 100, stdin) == NULL){
            continue;
        }
        
        if(strlen(input) != 2 || input[1] != '\n'){
            printf("Error - please enter only one character\n");
            continue;
        }
        
        rank = input[0];
        
        if(search(target, rank) == 1){
            return rank;
        } else {
            printf("Error - must have at least one card from rank to play\n");
        }
    }
}









