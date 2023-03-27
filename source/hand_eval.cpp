#include "hand_eval.h"
#include "tx_hld_key.h"
#include "card.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

/*
g++ -std=c++17 card.cpp tx_hld_key.cpp hand_eval.cpp -o test
*/

HandEval::HandEval() { this->tx_key = new TexasHoldemKey; }

HandEval::~HandEval() { delete this->tx_key; }


// returns hand rank 0 == Royal Flush   
int HandEval::eval(std::vector<Card*>& cards) {

    if ( cards.size() < 5 ) { return -1; }

    std::string res = check_hand(cards);
    //std::cout << res << std::endl;

    return tx_key->key.at(res);
}

// returns best hand out of cards
std::string HandEval::best_hand(std::vector<Card*>& cards) {

    if ( cards.size() < 5 ) { return "Invalid Hand Size"; }

    return check_hand(cards);
}


std::string HandEval::check_hand(std::vector<Card*>& cards) {

    //reset map keys to 0's
    reset_maps();

    // fill map keys with card values
    fill_maps(cards);

    // -1 if no straight, high card if straight
    int straight = check_straight();

    // -1 if no flush, suit number if flush
    int flush = check_flush();

    // -1 if no straight flush, high card if straight flush
    int straight_flush = -1;
    if (straight != -1 && flush != -1) { straight_flush = check_straight_flush(flush);}

    // -1 if no four of a kind, card number if four of a kind
    int fours = check_fours();

    std::vector<int> threes;
    std::vector<int> pairs;

    // empty if no three of a kind, if three of a kind push_back to vector, high card first
    check_threes(threes);

    //// empty if no pairs , if pairs  push_back to vector, high card first
    check_pairs(pairs);



    std::string hand_str_code = "";
    int card_num;
    char card_char_code;

    if ( ( straight_flush != -1 ) ) { // Straight Flush
        
        return make_str( straight_flush, 5, true ) + 'R'; // straight(5) + hand type symbol(1)

    }
    else if ( fours != -1 ) { // four of a kind

        return make_str( fours, 4, false ) + add_high_cards( &fours, NULL, 1) + '^'; // fours(4) + high card(1) + hand type symbol(1)

    }
    else if ( threes.size() && pairs.size() ) { // full house 1 three 

        return make_str( (threes.at(0)), 3, false ) + make_str( (pairs.at(0)), 2, false ) + 'H'; // threes(3) + pair(2) + hand type symbol(1)
    }
    else if (threes.size() > 1) {

        return make_str( (threes.at(0)), 3, false ) + make_str( (threes.at(1)), 2, false ) + 'H'; // high threes(3) + low_threes(2) + hand type symbol(1)
    }
    else if ( flush != -1 ) { // flush

        return make_str_flush(flush) + 'F'; // flush(5) + hand type symbol(1)
    }
    else if ( straight != -1 ) { // straight

        return make_str( straight, 5, true ) + 'S'; // straight(5) + hand type symbol(1)
    }
    else if ( threes.size() ) { // three of a kind

        return make_str( (threes.at(0)), 3, false ) + add_high_cards( &(threes.at(0)), NULL, 2 ) + '*'; // threes(3) + high cards(2) + hand type symbol(1)
    }
    else if ( pairs.size() > 1 ) { // 2 pairs

        return make_str( (pairs.at(0)), 2, false ) 
            + make_str( (pairs.at(1)), 2, false ) 
            + add_high_cards( &(pairs.at(0)), &(pairs.at(1)), 1) 
            + '+';
        // high pair(2) + low pair(2) + high card(1) + hand type symbol(1)
    }
    else if ( pairs.size() ) { // 1 pair

        return make_str( (pairs.at(0)), 2, false ) + add_high_cards( &(pairs.at(0)), NULL, 3 ) + 'P'; // pair(2) + high cards(3) + hand type symbol(1)
    } 
    else { // high card

        return add_high_cards( NULL, NULL, 5 ) + 'C'; // high cards(5) + hand type symbol
    }

    return "ERROR";
}


std::string HandEval::make_str(int card_num, int reps, bool decrement) {

    std::string res = "";
    char char_code;

    for (int i = 0; i < reps; i++) {
        char_code = num_to_char[card_num];
        res.push_back(char_code);

        // if straight
        if ( decrement ) {
            card_num--; 
            if (card_num < 0) { card_num = 12; }
        }
    }

    return res;
}

std::string HandEval::make_str_flush(int suit_num) {


    std::vector<int> fkey(13);
    for ( int i = 0; i < 13; i++ ) { fkey.at(i) = 0; }

    std::string res = "";
    char char_code;
    int card_num;

    for (int i = 0; i < this->SFMap[suit_num].size(); i++) {

        card_num = this->SFMap[suit_num].at(i);
        fkey.at(card_num) = 1;

    }

    for (int i = 12; i >= 0; i--) {

        if ( fkey.at(i) == 1 ) {
            char_code = num_to_char[i];
            res.push_back(char_code);
        }
        if (res.size() == 5) {
            break;
        }
    }

    return res;
}

std::string HandEval::add_high_cards(int* card1, int* card2, int reps) {

    std::unordered_map<int, int> invalid;
    std::string res = "";
    int high_card = 12;
    char char_code;

    if ( card1 ) { invalid[(*card1)] = 1; }
    if ( card2 ) { invalid[(*card2)] = 1; }

    while ( (reps > 0) && (high_card >= 0) ) {
        
        if (invalid.count(high_card) || (numMap[high_card] == 0) ) { // if invalid card of not existant
            high_card--;
            continue;
        }
        else if ( numMap[high_card] > 0 ) { // add possible card dont worry about repeats, cause that would be a full house of 2 pairs
            
            char_code = num_to_char[high_card];
            res.push_back(char_code);
            reps--;
        }
        high_card--;
    }

    return res;
}

void HandEval::fill_maps(std::vector<Card*>& cards) {

    int n;
    int s;
    for (int i = 0; i < cards.size(); i++) {
        n = cards.at(i)->number;
        this->numMap[n]++;
        s = cards.at(i)->suit;
        this->suitMap[s]++;
        this->SFMap[s].push_back(n);
    }

}

// 
void HandEval::reset_maps() {

    this->suitMap = {
            {0, 0}, //Diamond
            {1, 0}, //Club
            {2, 0}, //Heart
            {3, 0}, //Spades
    };

    this->numMap = {
            {0, 0},
            {1, 0},
            {2, 0},
            {3, 0},
            {4, 0},
            {5, 0},
            {6, 0},
            {7, 0},
            {8, 0},
            {9, 0},
            {10, 0},
            {11, 0},
            {12, 0},
    };

    this->SFMap = {
            {0, {}}, //Diamond
            {1, {}}, //Club
            {2, {}}, //Heart
            {3, {}}, //Spades
        };

}

// returns -1 if no straignt, highcard if straight
int HandEval::check_straight() {

    //check for straight, loops through ace to ace
    unsigned int straightCheck = 0;
    unsigned int straight_high = -1;
    if (this->numMap[12] > 0) {
        straightCheck++;
    }
    for (int i = 0; i < 13; i++) {
    
        if (this->numMap[i] > 0) {
            straightCheck++;
            if (straightCheck >= 5) {
                straight_high = i;
            }
        }
        else {
            straightCheck = 0;
        }
    }
    return straight_high;
}

// returns -1 if no flush, suit if flush
int HandEval::check_flush() {

    //check for flush, loops suitMap
    for (int i = 0; i < 4; i++) {

        if (this->suitMap[i] >= 5) {
            return i;
        }
    }
    return -1;
}

// returns -1 if no straight flush, high card if straight flush
int HandEval::check_straight_flush(int suit_num) {

    if (this->SFMap[suit_num].size() < 5 || suit_num == -1) {
        return -1;
    }

    std::vector<int> fkey(13, 0);
    //for ( int i = 0; i < 13; i++ ) { fkey.at(i) = 0; }

    // make key
    int card_num;
    for (int i = 0; i < this->SFMap[suit_num].size(); i++) {
        card_num = this->SFMap[suit_num].at(i);
        fkey.at(card_num) = 1;
    }


    //check for straight, loops through ace to ace
    unsigned int straightCheck = 0;
    unsigned int straight_high = -1;
    if (fkey.at(12) == 1) {
        straightCheck++;
    }
    for (int i = 0; i < 13; i++) {
    
        if (fkey.at(i) == 1) {
            straightCheck++;
            if (straightCheck >= 5) {
                straight_high = i;
            }
        }
        else {
            straightCheck = 0;
        }
    }
    return straight_high;
}

// returns -1 if no four of a kind, card num if four of a kind
int HandEval::check_fours() {

    //check for four of a kind, loops numMap
    for (int i = 12; i >= 0; i--) {

        if (this->numMap[i] >= 4) {
            return i;
        }
    }
    return -1;
}

// leaves vector empty if no three of a kind, threes.push_back card num if three of a kind
void HandEval::check_threes(std::vector<int>& threes) {

    //check for three of a kind, loops suitMap
    for (int i = 12; i >= 0; i--) {
        if (this->numMap[i] == 3) {
            threes.push_back(i);
        }
    }
    return;
}

// leaves vector empty if no pairs, pairs.push_back card num if pair
void HandEval::check_pairs(std::vector<int>& pairs) {

    //check for three of a kind, loops suitMap
    for (int i = 12; i >= 0; i--) {
        if (this->numMap[i] == 2) {
            pairs.push_back(i);
        }
    }
    return;
}


/*
int main(int argc, char* argv[]) {


    HandEval eval;

    std::vector<Card*> hand;

    int num;
    for (int i = 1; i < argc; i++) {
        std::string val(argv[i]);
        num = std::stoi(val);
        hand.push_back(new Card(num));
        hand.back()->displayCard();
    }

    std::cout << eval.eval(hand) << std::endl;


    for (int i = 0; i < argc-1; i++) {
        delete hand.at(i);
    }

    return 0;
}
*/
