#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

int DEBUG = 0;
deck_ptr deck = NULL;

card_ptr next_card(FILE *);


main(int argc, char **argv) {
  card_ptr c;
  FILE *input_deck;
  int cards_in_play = 0;
  input_deck = stdin;
  if (argc > 1) {
     DEBUG = atoi(argv[1]);
  }
  printf("Ready to play...\n");
  while ((c = next_card(input_deck)) != NULL) {
     int done = 0;
     deck = add_deck(c,deck);
     cards_in_play++;
     while (!done) {
        if (cards_in_play < 4) done = 1;
        else {
          card_ptr top_card = get_topcard(deck);
          card_ptr compare_card = get_comparecard(deck);
          if (DEBUG) 
             if (top_card && compare_card){ 
               printf("comparing ");
               print_card(top_card);
               print_card(compare_card);
               printf("\n");
             }
          if (compare_suit(top_card,compare_card)) {
	     if (DEBUG) printf("   Suits match\n");
             deck = remove_two(deck);
             cards_in_play -= 2;
          } else if (compare_face(top_card,compare_card)) {
	     if (DEBUG) printf("   Faces match\n");
             deck = remove_four(deck); done = 1;
             cards_in_play -= 4;
          } else done = 1;
        }
     }
  }
   output_deck(deck);
   delete_deck(deck);
}



card_ptr next_card(FILE *input_file) {
   char in1,in2;
   card_ptr c; 
   if (fscanf(input_file,"%c%c ",&in1,&in2) != EOF) {
      int face;  suit_type suit;
      switch(in1) {
        case 'A': case 'a': face = 1; break;
        case 'T': case 't': face = 10; break;
        case 'J': case 'j': face = 11; break;
        case 'Q': case 'q': face = 12; break;
        case 'K': case 'k': face = 13; break;
        case '2': case '3': case '4': 
        case '5': case '6': case '7': 
        case '8': case '9':  face = in1 - '0'; break; 
        default :return NULL;
      }
      switch(in2) {
        case 'S': case 's': suit = SPADE; break;
        case 'H': case 'h': suit = HEART; break;
        case 'D': case 'd': suit = DIAMOND; break;
        case 'C': case 'c': suit = CLUB; break;
        default : return NULL;
      }
      c = new_card(face,suit);
      return c;
   } else 
   return NULL;
}

print_card(card_ptr c) {
  switch (c->face) {
    case 1: printf("[ACE,"); break;
    case 11: printf("[JACK,"); break;
    case 12: printf("[QUEEN,"); break;
    case 13: printf("[KING,"); break;
    case 2: case 3: case 4:
    case 5: case 6: case 7:
    case 8: case 9: case 10: printf("[%d,",c->face);
  }
  switch (c->suit) {
    case HEART: printf("H] "); break;
    case SPADE: printf("S] "); break;
    case DIAMOND: printf("D] "); break;
    case CLUB: printf("C] "); break;
   }
}
