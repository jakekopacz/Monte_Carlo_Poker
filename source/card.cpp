#include <iostream>
#include <iomanip>
#include <vector>
#include "card.h"


const std::string Card::displayNumber[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eigth", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
const std::string Card::displaySuit[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
//default constructor
Card::Card() {
    ID = -1;
    number = -1;
    suit = -1;
}

//paramitized constructor
Card::Card(int num) {
    ID = num;
    number = num % 13;
    suit = num / 13;
}

//Copy constructor
Card::Card(Card &obj) {
    this->number = obj.number;
    this->suit = obj.suit;
}

//Destructor
Card::~Card() {
    //No dynamic memory is allocated
    //std::cout << "Delete this CARD from my memory" << std::endl;
}

//Display the card
void Card::displayCard() {

    if (number == -1 || suit == -1) {
        std::cout << "This card is wackadazical" << std::endl;
    }
    else {
        std::cout << displayNumber[number] << " of " << displaySuit[suit] << std::endl;
    }
    
}

/*
int main() {


    Card myCard2(0);

    Card myCard3(myCard2);

    Card myCard4 = myCard2;

    myCard2.displayCard();
    myCard3.displayCard();
    myCard4.displayCard();

    return 0;
}
*/

