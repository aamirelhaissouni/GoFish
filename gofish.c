#include <stdio.h>
#include <time.h>
#include "deck.h"
#include "player.h"

int main(int args, char* argv[]) 
{
    /*
    //JUST SOME STUFF I USED TO TEST
    struct player* user_p = &user;
    struct player* computer_p = &computer;

    fprintf(stdout, "Put your code here.\n");
    fflush(stdout);

    printf("\n");
    printf("\n");

    //test shuffle()
    shuffle();
    fprintf(stdout, "Deck initialized!\n");

    printf("\n");
    printf("\n");

    //test deal_player cards()
    deal_player_cards(user_p);
    struct hand* current_card = user_p->card_list;

    printf("Printing player's hand:\n");
    int count = 0;
    while(current_card != NULL){
        printf("Card %d: %s of %c\n", count, current_card->top.rank, current_card->top.suit);
        current_card = current_card->next;
        count++;
    }
    fprintf(stdout, "Dealt cards to player!\n");  

    printf("\n");
    printf("\n");

    //test add_card() and next card()
    struct card* new_card = next_card();
    add_card(user_p, new_card);

    current_card = user_p->card_list;
    printf("Printing player's hand:\n");
    count = 0;
    while(current_card != NULL){
        printf("Card %d: %s of %c\n", count, current_card->top.rank, current_card->top.suit);
        current_card = current_card->next;
    }

    fprintf(stdout, "Successfully added new card to player from deck!\n");

    //need to test: remove_card, check_add_book, and search

    printf("\n");
    printf("\n");

    //test remove_card()
    struct card target_card = user_p->card_list->top;
    remove_card(user_p, &target_card);

    current_card = user_p->card_list;
    printf("Printing player's hand:\n");
    count = 0;
    while(current_card != NULL){
        printf("Card %d: %s of %c\n", count, current_card->top.rank, current_card->top.suit);
        current_card = current_card->next;
        count++;
    }
    printf("Successfully removed top card form players hand! \n");

    printf("\n");
    printf("\n");

    //test check_add book
    char ret_value = check_add_book(user_p);
    printf("%c\n", ret_value);
    printf("Successfully checked player for address book!\n");

    printf("\n");
    printf("\n");

    //test search
    char search_target = '8';
    printf("Searching if %c is in user's hand.\n", search_target); 
    int search_result = search(user_p, search_target); 
    printf("Search result was: %d\n", search_result);

    printf("\n");
    printf("\n");

    //test transfer_cards next
    printf("Testing transfer of cards: \n");
    transfer_cards(user_p, computer_p, '8');
        
    current_card = user_p->card_list;
    printf("Printing player's hand:\n");
    count = 0;
    while(current_card != NULL){
        printf("Card %d: %s of %c\n", count, current_card->top.rank, current_card->top.suit);
        current_card = current_card->next;
        count++;
    }

    current_card = computer_p->card_list;
    printf("Printing computer's hand:\n");
    count = 0;
    while(current_card != NULL){
        printf("Card %d: %s of %c\n", count, current_card->top.rank, current_card->top.suit);
        current_card = current_card->next;
        count++;
    }

    printf("Successfully transfered cards! \n");

    printf(" \n");
    printf(" \n");

    //test game over
    printf("Testing game over: \n");
    int test_game_over = game_over(user_p);
    if(test_game_over == 1){
        printf("Gameuh over-dah! \n");
    }else{
        printf("Gameuh notuh overdah! \n");
    }
    printf("Game over tested succesfurry! \n");

    printf(" \n");
    printf(" \n");

    //test reset_player next
    printf("Testing reset_player: \n");
    if(reset_player(user_p) != 0){
        printf("Reset player failed! \n");
    }else{
        printf("Reset player successful!");
    }

    printf(" \n");
    printf(" \n");
    */
    srand(time(NULL));

    if(shuffle() !=0 ){
        printf("Error in shuffling deck \n");
        return -1;
    }

    if(deal_player_cards(&user) != 0 || deal_player_cards(&computer) != 0){
        printf("Error dealing cards \n");
        return -1;
    }

    printf("Start Go Fish!\n");

    while(!game_over(&user) && !game_over(&computer)){

        //User goes first
        printf("\nYour turn friend! You have %zu cards.\n", user.hand_size);
        printf("Your books: ");
                for(int i = 0; i < 7; i++){
            if(user.book[i] != 0) printf("%c ", user.book[i]);
        }
        printf("\n");

        printf("Your hand: ");
        struct hand* current = user.card_list;
        while(current != NULL){
            printf("%c-%s, ", current->top.suit, current->top.rank);
            current = current->next;
        }
        printf("\n");
        
        char user_rank = user_play(&user);
        printf("You asked for: %c\n", user_rank);
        
        if(search(&computer, user_rank)){
            int transferred = transfer_cards(&computer, &user, user_rank);
            printf("Computer gives you %d card(s)\n", transferred);
            char book = check_add_book(&user);
            if(book != 0){
                printf("You completed a book: %c\n", book);
            }
        } else {
            printf("Go Fish!\n");
            struct card* new_card = next_card();
            if(new_card != NULL){
                add_card(&user, new_card);
                char book = check_add_book(&user);
                if(book != 0){
                    printf("You completed a book: %c\n", book);
                }
            }
        }
        
        if(game_over(&user) || game_over(&computer)) break;

        //COmputer goes next
        printf("\nComputer's turn. Computer has %zu cards.\n", computer.hand_size);
        char computer_rank = computer_play(&computer);
        printf("Computer asks for: %c\n", computer_rank);
        
        if(search(&user, computer_rank)){
            int transferred = transfer_cards(&user, &computer, computer_rank);
            printf("You give computer %d card(s)\n", transferred);
            char book = check_add_book(&computer);
            if(book != 0){
                printf("Computer completed a book: %c\n", book);
            }
        } else {
            printf("Computer goes fishing!\n");
            struct card* new_card = next_card();
            if(new_card != NULL){
                add_card(&computer, new_card);
                char book = check_add_book(&computer);
                if(book != 0){
                    printf("Computer completed a book: %c\n", book);
                }
            }
        }
    }

    // Game over - determine winner
    printf("\n=== Game Over ===\n");
    int user_books = 0, computer_books = 0;
    
    for(int i = 0; i < 7; i++){
        if(user.book[i] != 0) user_books++;
        if(computer.book[i] != 0) computer_books++;
    }
    
    printf("Your books: %d\n", user_books);
    printf("Computer books: %d\n", computer_books);
    
    if(user_books > computer_books){
        printf("You win!\n");
    } else if(computer_books > user_books){
        printf("Computer wins!\n");
    } else {
        printf("It's a tie!\n");
    }
    
    return 0;
}
