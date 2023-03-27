#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_set>
#include "deck.h"
#include "card.h"


//default constructor, makes deck of 52 unique cards
Deck::Deck() {

    for (int i = 0; i < deckSize; i++) {
       myDeck.push_back(new Card(i));
    }
}

//special constructor, makes deck of 52-exlcude.size() unique cards
Deck::Deck(std::unordered_set<int>& exclude, int size) {

    for (int i = 0; i < deckSize; i++) {
        if (exclude.count(i)) {
            continue;
        }
       myDeck.push_back(new Card(i));
    }
    deckSize -= size;
}

//destructor, deletes cards allocated to heap
Deck::~Deck() {

    for (int i = 0; i < deckSize; i++) {
        delete myDeck.at(i);  
    }
}

//Shuffles deck, returns DeckIndex to zero
void Deck::shuffleDeck() {

    Card* temp;
    for (int i = 0; i < deckSize; i++) {
        
        int r = rand() % deckSize;

        temp =  myDeck.at(i);

        myDeck.at(i) = myDeck.at(r);
        myDeck.at(r) = temp;
    }
    deckIndex = 0;
}

//Deals one card to player passed through, increments DeckIndex by 1
/*
void Deck::dealDeckToPlayer(Player *p, int handIndex) {

    if (deckIndex >= deckSize) {
        std::cout << "Out of index: Deck";
        return;
    }
    
    p->addToHand(myDeck.at(deckIndex),handIndex);
    deckIndex++;
}
*/

Card* Deck::deal() {

    if (deckIndex >= deckSize) {
        std::cout << "Out of index: Deck";
        return nullptr;
    }
    
    Card* tmp = myDeck.at(deckIndex);
    deckIndex++;

    return tmp;
}
