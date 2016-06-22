#include <stdlib.h>
#include <stdio.h>

#include "deck.h"

/*
One handed solitaire
Alec Webb
*/

card_ptr new_card(int face, suit_type suit) {
   card_ptr t = (card_ptr)malloc(sizeof(card_rec));
   t->face = face;
   t->suit = suit;
   return t;
}

int compare_face(card_ptr card1, card_ptr card2) {
   if (card1 == NULL || card2 == NULL) return 0;
   return card1->face == card2->face;
}

int compare_suit(card_ptr card1, card_ptr card2) {
   if (card1 == NULL || card2 == NULL) return 0;
   return card1->suit== card2->suit;
}

void output_deck(deck_ptr deck) {
  if (deck) {
    printf("\nResult: ");
    while (deck) {
       print_card(deck->card);
       deck=deck->next; 
    }
  } else printf("You Won!!");
  printf("\n");
}
/* Implement the functions below: */

card_ptr get_topcard(deck_ptr deck) {
/* return ptr to card at top of deck */
  card_ptr topcard = deck->card;	//point to top card on deck
  
  return topcard;
}

card_ptr get_comparecard(deck_ptr deck) {
/* return pointer to fourth card from the top of the deck */
  card_ptr fourthcard = deck->next->next->next->card;	//point to fourth card in deck

  return fourthcard;  
}

deck_ptr add_deck(card_ptr c, deck_ptr deck) {
  /* 'push' the card onto the deck */
  deck_ptr temp = (deck_ptr)malloc(sizeof(deck_rec));   //create temporary node
  temp->card = c;										//assign properties of node
  temp->next = deck;
  deck = temp;											//make the new node the head
    
  return deck;
}

deck_ptr remove_two(deck_ptr deck) {
  /* remove cards 2 and 3 (from the top) and return a pointer to the new deck - be sure to
   fix up the pointers correctly */
   deck_ptr second = deck->next;		//point to second position card
   deck_ptr third = deck->next->next;	//point to third position card
   
   deck->next = deck->next->next->next;	//reassign pointer from first card to fourth
   
   free(second);						//free the second and third
   free(third);
      
  return deck;
}

deck_ptr remove_four(deck_ptr deck) {
   /* remove the top four cards on the deck and return a pointer to the new deck */
   deck_ptr first = deck;						//point to the first four cards
   deck_ptr second = deck->next;
   deck_ptr third = deck->next->next;
   deck_ptr fourth = deck->next->next->next;
   
   deck = deck->next->next->next->next;			//make the top of the deck the fifth card
   
   free(first);									//free the first four
   free(second);
   free(third);
   free(fourth);

  return deck;
}

void delete_deck(deck_ptr deck) {
  /* free all of the space used */
  deck_ptr temp;
  while(deck){							//free the entire deck by cycling through
	temp = deck;						//and freeing memory one by one.
	deck = deck->next;
	free(temp);
  }
}