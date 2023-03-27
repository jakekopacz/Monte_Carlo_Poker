
#ifndef _DECK_H_
#define _DECK_H_
#include <string>
#include <vector>
#include <unordered_set>
#include "card.h"


class Deck {

    public:

        //default constructor, creates 52 unique cards
        Deck();

        Deck(std::unordered_set<int>& exclude, int size);
    
        //destructor, deletes 52 cards allocated to heap
        ~Deck();

        //shuffles deck, sets deckIndex to 0
        void shuffleDeck();

        Card* deal();

        //void dealDeckToPlayer(Player *p, int HandIndex);

        //A DECK of 52 unique cards
        std::vector<Card *> myDeck;


    private:
        friend class Monte;
        //keeps track of index to deal cards
        int deckIndex = 0;
        unsigned int deckSize = 52;


};
#endif
