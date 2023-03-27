# Monte Carlo Poker

Monte Carlo Simulation for Texas Holdem Poker written 100% in C++ using only the standard library.

## Overview
A Monte Carlo Algorithm uses repetitive random sampling to determine the probability of an event. This project takes this concept and applies it to determine the probability of poker hands.

- Included in this project:
  - Monte Carlo Algorithm
  - Poker Hand Evaluator
  - Poker Hand Rank Dictionary
  - Card Class

### Monte Carlo Algorithm

This Monte Carlo Algorithm determines the likelyhood of a player(s)' hand winning or splitting the pot by running *n* iterations of a poker game. In which it deals random cards and determines the winner after every iteration.

This program only has one public funtion which can either print results to the terminal or modify a vector passed through it.

Public Functin Parameters:
- Hand     = player's hand = 2 cards
- com      = games' com cards, 0 - 5
- nc       = number of com cards
- np       = number of players (player + other)
- it       = number of iterations for simulation to run
- others   = other players cards, NULL if unknown
- results  = will set vector to results, NULL if just want a terminal print out (row = player) (column 1 = wins, column 2 = splits)

```c++
void Monte::sim( vector<Card*>& hand, vector<Card*>& com, unsigned int nc, unsigned int np, unsigned int it, vector<vector<Card*> >* others_cards, vector<vector<int> >* results)
```
Example of 1:
```
Community Cards = Ace of Hearts, 2 of Spades, 5 of Clubs
Player Cards = Ace of Clubs, Ace of Diamonds
sim(hand, com, 3, 4, 10000, NULL, NULL);

***** OUT OF 10000 GAMES *****

Player Wins:   8303    83.03%
Player Splits: 78    0.78%
```
Example 2:
```
Community Cards = Ace of Hearts, 2 of Spades, 5 of Clubs
Player 1 Cards = Ace of Clubs, Ace of Diamonds
Player 2 Cards = Ace of Spades, Five of Diamonds
Player 3 Cards = 6 of Hearts, 7 of Spades
Player 4 Cards = 8 of Hearts, 9 of Hearts

sim(hand, com, 3, 4, 1000, &others, NULL);

***** OUT OF 10000 GAMES *****

Player 1 Wins:   9149
Player 1 Splits: 0

Player 2 Wins:   17
Player 2 Splits: 0

Player 3 Wins:   450
Player 3 Splits: 0

Player 4 Wins:   384
Player 4 Splits: 0
```

### Hand Evaluator

The HandEval class defined in hand_eval.h & hand_eval.cpp evaluates a 5 - 7 card hand and determines the best hand. This is achieved primarily through algorithms using hashmaps.


Returns the best hand out of the cards passed through. Return string is 6 char long, and the same format used in the TexasHoldemKey.
```cpp
std::string best_hand(std::vector<Card*>& cards);
```
Returns the rank of the best hand out of the cards passed through.
```cpp
int eval(std::vector<Card*>& cards);
```
Example of seven cards passed through
```
./handEval 12 25 38 0 13 44 6
Cards: 
Ace of Clubs
Ace of Diamonds
Ace of Hearts
Two of Clubs
Two of Diamonds
Seven of Spades
Eigth of Clubs

Best Hand: AAA22H
Hand Rank: 177
```

### Database

There are $52 \choose 5$ poker hands. However, there are only 7,642 different strengths of hands, as demonstrated below.

| Hand Type       | Second Header |
| --------------- | --------------------- |
| Straight Flush  | $$10$$  |
| Four of a Kind  | $$13*12$$  |
| Full House      | $$13*12$$  |
| Flush           | $\frac{13*12*11*10*9}{5*4*3*2*1}$  |
| Straight        | $10$  |
| Three of a kind | Content Cell  |
| Two Pairs       | Content Cell  |
| Pair            | Content Cell  |
| High Card       | Content Cell  |
```math
Straight Flush  =    A to 5 high  =    10 
Four of a Kind  =    13 * 12      =    156                                = 156
Full House      =    13 * 12      =    156                             = 156
Flush           =    ((13*12*11*10*9) / (5*4*3*2*1)) - 10    = 1277 (SUBTRACT 10 FOR STRAIGHT FLUSH)
Straight        =    1608    =    10                                      = 10
Three of a Kind =    2466    =    13 * ((12*11) / (2*1))                  = 858
Two Pairs       =    3325    =    ((13*12) / 2) * 11                      
Pair            =    6185    =    13 * ((12*11*10) / (3*2*1))             
High Card       =    7462    =    ((13*12*11*10*9) / (5*4*3*2*1)) - 10
```
The TexasHoldemKey class defined in tx_hold_key.h & tx_hold_key.cpp creates a hash map of the 7,642 unique hands(key) and ranks(value) them from 0 (Royal Flush) to 7,641 (7,5,4,3,2).
String Code:
- Cards sorted by priotity, then value
  - "22J94P" -> Pair of 2s
  - "AJ739F" -> Flush Ace High
  - "JJ77K+" -> 2 pairs Jacks & 7s, high card King

Hash Map: 
- "AKQJTR" = 0     - Royal Flush
- "75432C" = 7,641 - 7,5,4,3,2 off suit

The public function int hand_rank(std::sting hand) takes in a 6 character string and returns the hand's rank


## Installation & Running

```
$ pip install deuces
```

## Implimentation

### Uses

