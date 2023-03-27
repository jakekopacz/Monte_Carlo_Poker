#include "monte_carlo_poker.h"
#include "card.h"
#include <ctime>
#include <iostream>
#include <string>
#include <vector>


// convert time to int
int time_to_num(std::string& ctime_str) {

    int res;
    std::string num;

    for (int i = 0; i < ctime_str.size(); i++) {
        if (ctime_str.at(i) >= '0' && ctime_str.at(i) <= '9') {
            num.push_back(ctime_str.at(i));
        }
        if (num.size() >= 6) {
            break;
        }
    }

    res = std::stoi(num);
    return res;
}


int get_input() {

    int input = 0;

    while (input > 3 || input < 1) {

        std::cout << std::endl;
        std::cout << "Enter 1 for Blind Sim" << std::endl;
        std::cout << "Enter 2 for Known Sim" << std::endl;
        std::cout << "Enter 3 to Exit Sim" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter Choice:  ";
        std::cin >> input;

    }

    return input;
}

Card* get_card() {

    int input = -1;

    while (input > 51 || input < 0) {

        std::cout << "Enter Card Number 0 - 51 (2 through ace, Clubs, Diamonds, Hearts, Spades):  ";
        std::cin >> input;
    }
    Card* tmp = new Card(input);

    return tmp;
}

int make_player(std::vector<Card*>& player) {


    // poker with more than six people sucks
    int n_players = 0;
    while (n_players > 6 || n_players < 2) {
        std::cout << std::endl;
        std::cout << "Enter Number of Players (2 - 6):  ";
        std::cin >> n_players;
    }

    std::cout << std::endl;
    std::cout << "*** Enter Your Cards (Player 1) ***" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < 2; i++) {

        player.push_back(get_card());
    }

    return n_players;
}

int make_com(std::vector<Card*>& com_cards) {
    
    std::cout << std::endl;
    std::cout << "*** Enter Community Cards ***" << std::endl;

    // who sims the blind bet ???
    int n_com_cards = 0;
    while (n_com_cards > 5 || n_com_cards < 3) {
        std::cout << std::endl;
        std::cout << "Enter Number of Com Cards (3 - 5) ";
        std::cin >> n_com_cards;
    }

    std::cout << std::endl;
    for (int i = 0; i < n_com_cards; i++) {

        com_cards.push_back(get_card());
    }

    return n_com_cards;
}


void make_others(std::vector<std::vector<Card*> >& other_hands, int n_others) {

    other_hands = std::vector<std::vector<Card*> >(n_others, std::vector<Card*>(2, nullptr));

    std::cout << std::endl;
    std::cout << "*** Enter Other Players Cards ***" << std::endl;
    for (int i = 0; i < n_others; i++) {
        std::cout << "Player " << (i+2) << ": " << std::endl;
        for (int j = 0; j < 2; j++) {
            other_hands.at(i).at(j) = get_card();
        }
    }

}

void delete_others(std::vector<std::vector<Card*> >& other_hands) {

    int n = other_hands.size();
    while (!other_hands.empty()) {

        while (!other_hands.back().empty()) {
            f++;
            delete other_hands.back().back();
            other_hands.back().pop_back();
        }
        other_hands.pop_back();
    }

}

void delete_cards(std::vector<Card*>& com_cards, std::vector<Card*>& player) {
    
    while (!player.empty()) {
        delete player.back();
        player.pop_back();
    }

    while (!com_cards.empty()) {
        delete com_cards.back();
        com_cards.pop_back();
    }
}

int main() {


    /* seed random with current time */
    time_t curr_time;
    time(&curr_time);
    std::string time_str(ctime(&curr_time));
    int seed_val = time_to_num(time_str);
    std::srand(seed_val);


    /* CREATE  MONTE CARLO OBJECT*/
    Monte sim;

    /* PLAYERS HAND, COM CARDS, AND OTHER PLAYERS HANDS */
    std::vector<Card*> hand;
    std::vector<Card*> com_cards;
    std::vector<std::vector<Card*> >other_hands;


    unsigned int input = 0;
    unsigned int n_players;
    unsigned int n_com_cards;
    unsigned int itterations = 0;
    while (input != 3) {

        input = get_input();
        if (input == 3) {
            std::cout << "GoodBye" << std::endl;
            break;
        }

        n_players = make_player(hand);

        n_com_cards = make_com(com_cards);

        std::cout << std::endl;
        while (itterations < 1) {
            std::cout << "Enter Itterations: ";
            std::cin >> itterations;
        }
        std::cout << std::endl;


        if (input == 1) {
            sim.sim(hand, com_cards, n_com_cards, n_players, itterations, NULL, NULL);
        }
        else if (input == 2) {
            make_others(other_hands, (n_players-1));
            sim.sim(hand, com_cards, n_com_cards, n_players, itterations, &other_hands, NULL);
            delete_others(other_hands);
        }
        delete_cards(com_cards, hand);
    }

    return 0;
}