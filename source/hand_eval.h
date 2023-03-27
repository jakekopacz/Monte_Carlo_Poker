#ifndef _HAND_EVAL_H_
#define _HAND_EVAL_H_
#include "tx_hld_key.h"
#include "card.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>


class HandEval {

    public:

        HandEval();
        ~HandEval();

        //returns best hand o
        std::string best_hand(std::vector<Card*>& cards);

        //returns card rank
        int eval(std::vector<Card*>& cards);

    private:

        std::string check_hand(std::vector<Card*>& cards);

        std::string make_str(int card_num, int reps, bool decrement);

        std::string make_str_flush(int suit_num);

        std::string add_high_cards(int* card1, int* card2, int reps);

        //adds cards to suitMap & numMap
        void fill_maps(std::vector<Card*>& cards);

        void reset_maps();

        int check_straight();

        int check_straight_flush(int suit_num);

        int check_flush();

        int check_fours();

        void check_threes(std::vector<int>& threes);

        void check_pairs(std::vector<int>& pairs);


        TexasHoldemKey* tx_key;

        std::unordered_map<int, unsigned int> suitMap {
            {0, 0}, //Diamond
            {1, 0}, //Club
            {2, 0}, //Heart
            {3, 0}, //Spades
        };

        std::unordered_map<int, std::vector<int> > SFMap {
            {0, {}}, //Diamond
            {1, {}}, //Club
            {2, {}}, //Heart
            {3, {}}, //Spades
        };

        std::unordered_map<int, unsigned int> numMap = {
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

        std::unordered_map<int, char> num_to_char = {
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
