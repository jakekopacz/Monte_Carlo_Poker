
#ifndef _TX_HLD_KEY_
#define _TX_HLD_KEY_
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

/*

HANDS ARE RANKED 0 - 7462
0       =   Royal Flush
7562    =   7-5-4-3-2


5 card hand Texas Holdem Poker has 
Straight Flush =    9       =    10                                      = 10
Four of a Kind =    165     =    13 * 12                                 = 156
Full House     =    321     =    13 * 12                                 = 156
Flush          =    1598    =    ((13*12*11*10*9) / (5*4*3*2*1)) - 10    = 1277 (SUBTRACT 10 FOR STRAIGHT FLUSH)
Straight       =    1608    =    10                                      = 10
Three ofa Kind =    2466    =    13 * ((12*11) / (2*1))                  = 858
Two Pairs      =    3325    =    ((13*12) / 2) * 11                      = 858
Pair           =    6185    =    13 * ((12*11*10) / (3*2*1))             = 2860
High Card      =    7462    =    ((13*12*11*10*9) / (5*4*3*2*1)) - 10    = 1277 (SUBTRACT 10 FOR STRAIGHT)


for all functions
2 = 0   ...   K = 11, A = 12
*/


class TexasHoldemKey {

    public:
        TexasHoldemKey();

        int hand_rank(std::string input);

    private:
        friend class HandEval;
        //construct helper
        void add_to_key();
        void hand_to_str();

        //construct helper
        void make_straight_flush();
        void make_fours();
        void make_full_house();
        void make_flush_high(int type);
        void make_straight();
        void make_threes();
        void make_two_pairs();
        void make_pair();

        std::vector<int> hand;
        std::string str;
        int rank = 0;
        std::unordered_map<std::string, int> key;

        std::unordered_map<int, char> hand_to_char = {
            {-9, 'C'}, // high card
            {-8, 'P'}, // pair
            {-7, '+'}, // 2 pairs
            {-6, '*'}, // three
            {-5, 'S'}, // straight
            {-4, 'F'}, // flush
            {-3, 'H'}, // full house
            {-2, '^'}, // four
            {-1, 'R'}, // flush straight
            {0, '2'},
            {1, '3'},
            {2, '4'},
            {3, '5'},
            {4, '6'},
            {5, '7'},
            {6, '8'},
            {7, '9'},
            {8, 'T'},
            {9, 'J'},
            {10, 'Q'},
            {11, 'K'},
            {12, 'A'},
        };


};

#endif
