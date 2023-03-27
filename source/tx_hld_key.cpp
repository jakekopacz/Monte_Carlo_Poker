#include "tx_hld_key.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>


TexasHoldemKey::TexasHoldemKey() {

    make_straight_flush();
    make_fours();
    make_full_house();
    make_flush_high(-4);
    make_straight();
    make_threes();
    make_two_pairs();
    make_pair();
    make_flush_high(-9);
}

int TexasHoldemKey::hand_rank(std::string input) {
    if (input.size() != 6) {
        return -1;
    }

    if (!key.count(input)) {
        return -2;
    }

    return key.at(input);
}

void TexasHoldemKey::add_to_key() {
    if (!key.count(str)) {
        //if (rank) {std::cout << str << ": " << rank << std::endl;}
        key.emplace(str, rank);
        rank++;
    }

}

void TexasHoldemKey::hand_to_str() {
    str.clear();
    for (int i = 0; i < 6; i++) {
        str.push_back(hand_to_char.at(hand.at(i)));
    }
}

void TexasHoldemKey::make_straight_flush() {

    hand = {12, 11, 10, 9, 8, -1};
    for ( ; rank < 10; ) {

        hand_to_str();
        add_to_key();

        hand.at(0)--;
        hand.at(1)--;
        hand.at(2)--;
        hand.at(3)--;
        hand.at(4)--;

        if (hand.at(4) == -1) { hand.at(4) = 12; }
    }

}

void TexasHoldemKey::make_fours() {

    hand.at(5) = -2;
    for (int i = 12; i >= 0; i--) {
        hand.at(0) = i;
        hand.at(1) = i;
        hand.at(2) = i;
        hand.at(3) = i;
        
        for (int j = 12; j >= 0; j--) {
            if (j == i) {
                continue;
            }
            hand.at(4) = j;
            hand_to_str();
            add_to_key();
        }
    }
}

void TexasHoldemKey::make_full_house() {

    hand.at(5) = -3;
    for (int i = 12; i >= 0; i--) {
        hand.at(0) = i;
        hand.at(1) = i;
        hand.at(2) = i;
        
        for (int j = 12; j >= 0; j--) {
            if (j == i) {
                continue;
            }
            hand.at(3) = j;
            hand.at(4) = j;
            hand_to_str();
            add_to_key();
        }
    }
}

void TexasHoldemKey::make_flush_high(int type) {

    hand.at(5) = type;
    for (int i = 12; i >= 5; i--) {
        hand.at(0) = i;
        
        for (int j = (i-1); j >= 3; j--) {
            hand.at(1) = j;

            for (int k = (j-1); k >= 2; k--) {
                hand.at(2) = k;

                for (int m = (k-1); m >= 1; m--) {
                    hand.at(3) = m;

                    for (int n = (m-1); n >= 0; n--) {
                        if (n == (i - 4)) {
                            continue;
                        }

                        hand.at(4) = n;
                        hand_to_str();
                        if (str == "A5432F") {
                            continue;
                        }
                        add_to_key();
                    }
                }
            }
        }
    }
}

void TexasHoldemKey::make_straight() {

    hand = {12, 11, 10, 9, 8, -5};
    for (int i = 0; i < 10; i++) {

        hand_to_str();
        add_to_key();

        hand.at(0)--;
        hand.at(1)--;
        hand.at(2)--;
        hand.at(3)--;
        hand.at(4)--;
        if (hand.at(4) == -1) { hand.at(4) = 12; }
    }

}

void TexasHoldemKey::make_threes() {

    hand.at(5) = -6;
    for (int i = 12; i >= 0; i--) {
        hand.at(0) = i;
        hand.at(1) = i;
        hand.at(2) = i;
        
        for (int j = 12; j >= 0; j--) {
            if (j == i) {continue;}
            hand.at(3) = j;
            for (int k = (j-1); k >= 0; k--) {
                if (k == i) { continue;}
                hand.at(4) = k;
                hand_to_str();
                add_to_key();

            }
        }
    }
}

void TexasHoldemKey::make_two_pairs() {

    hand.at(5) = -7;
    for (int i = 12; i >= 0; i--) {
        hand.at(0) = i;
        hand.at(1) = i;
        
        for (int j = (i-1); j >= 0; j--) {
            hand.at(2) = j;
            hand.at(3) = j;
            for (int k = 12; k >= 0; k--) {
                if (k == i || k == j) { continue;}
                hand.at(4) = k;
                hand_to_str();
                add_to_key();

            }
        }
    }
}

void TexasHoldemKey::make_pair() {

    hand.at(5) = -8;
    for (int i = 12; i >= 0; i--) {

        hand.at(0) = i;
        hand.at(1) = i;
        
        for (int j = 12; j >= 2; j--) {
            if (j == i) {continue;}

            hand.at(2) = j;

            for (int k = (j-1); k >= 1; k--) {
                if (k == i) { continue;}

                hand.at(3) = k;

                for (int m = (k-1); m >= 0; m--) {
                    if (m == i) {continue;}

                    hand.at(4) = m;
                    hand_to_str();
                    add_to_key();
                }

            }
        }
    }
}
