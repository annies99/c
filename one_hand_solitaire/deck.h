typedef enum {SPADE,HEART,DIAMOND,CLUB} suit_type;

typedef struct c {
  int face;  /* 1-13 */
  suit_type suit;
} card_rec, *card_ptr;

typedef struct p {
   card_ptr card;
   struct p *next;
} deck_rec, *deck_ptr;

card_ptr new_card(int face, suit_type suit); 
card_ptr get_topcard(deck_ptr deck);
card_ptr get_comparecard(deck_ptr deck);

deck_ptr add_deck(card_ptr card, deck_ptr deck); 
deck_ptr remove_two(deck_ptr deck);
deck_ptr remove_four(deck_ptr deck);
void output_deck(deck_ptr deck);
void delete_deck(deck_ptr deck);

