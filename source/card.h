
#ifndef _CARD_H_
#define _CARD_H_
#include <string>
#include <vector>

class Card {

    public:

        //default constructor
        Card();

        //paramitized constructor
        Card(int num);

        //copy constructor
        Card(Card &obj);

        //destructor
        ~Card();

        //display card num & suit
        void displayCard();

    private:
        friend class HandEval;
        friend class Monte;
        int ID;
        int number;
        int suit;

        const static std::string displayNumber[];
        const static std::string displaySuit[];

};
#endif
