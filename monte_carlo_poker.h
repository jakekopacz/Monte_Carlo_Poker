#ifndef _MONTE_CARLO_POKER_H_
#define _MONTE_CARLO_POKER_H_
#include "card.h"
#include "deck.h"
#include "hand_eval.h"
#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#include <iomanip>


class Monte {

    public:

        // constructor / destructor
        Monte();
        ~Monte();

        /*
            ** Public Function
            ** Hand     = player's hand = 2 cards
            ** com      = games' com cards, 0 - 5
            ** nc       = number of com cards
            ** np       = number of players (player + other)
            ** it       = number of iterations for simulation to run
            ** others   = other players cards, NULL if unknown
            ** results  = will set vector to results, NULL if just want a terminal print out (row = player) (column 1 = wins, column 2 = splits)
        */
        void sim(std::vector<Card*>& hand, std::vector<Card*>& com, unsigned int nc, unsigned int np, unsigned int it, std::vector<std::vector<Card*> >* others_cards, std::vector<std::vector<int> >* results);

    private:

        /* make static players & com_cards cards*/
        void make_vectors(std::vector<Card*>& hand, std::vector<Card*>& com, std::vector<std::vector<Card*> >* others_cards);

        /* delete player_hands & com_cards static cards*/
        void delete_vectors();

        /* add static cards to set, for deck constructor */
        void add_static_com_cards();
        /* add static cards to set, for deck constructor */
        void add_static_player_cards();

        /* deals deck to players */
        void deal_deck();

        /* clear cards dealt */
        void clear_hands();

        /* calls upon run_round, tallys results*/
        void run_sim(std::vector<std::vector<int> >* results);

        /* runs one iteration of game and determines winner(s)*/
        void run_round(std::vector<int>& winners);

        /* prints results of simulation */
        void print_res(std::vector<std::vector<int> >& score);



        std::vector<Card*> com_cards;
        std::vector<std::vector<Card*> > players;
        // cards which do not change during simulation
        std::unordered_set<int> static_cards;

        bool blind;
        unsigned int n_com_cards;
        unsigned int n_players;
        unsigned int p_hand_size = 2;
        unsigned int sim_iterations;

        // deck which contains all cards but static cards
        Deck* sim_deck;

        // evaluate hands
        HandEval* eval;
        

};
#endif