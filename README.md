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

### Poker Hand Dictionary

<details>

**<summary>There are $52 \choose 5$ poker hands. However, there are only 7,642 different strengths of hands, as demonstrated by clicking this drop down.</summary>**
  
| Hand Type       | Second Header | Number of hands | Sum of Hands|
| :-------------- | :---------------------: | :---: | :---: |
| Straight Flush  | $10$                | 10   | 10 |
| Four of a Kind  | $13*12$             | 156  | 166 |
| Full House      | $13*12$             | 156  | 322 |
| Flush           | $$\frac{13\cdot12\cdot11\cdot10\cdot9}{5\cdot4\cdot3\cdot2\cdot1}-10$$ | 1277 | 1,599|
| Straight        | $10$  | 10 | 1,609 |
| Three of a kind | $$13\cdot\frac{12\cdot11}{2\cdot1}$$ | 858 | 2,467 |
| Two Pairs       | $$\frac{13\cdot12}{2\cdot1}*11$$ | 858 | 3,325 |
| Pair            | $$13\cdot\frac{12\cdot11\cdot10}{3\cdot2\cdot1}$$ | 2860 | 6,185 |
| High Card       | $$\frac{13\cdot12\cdot11\cdot10\cdot9}{5\cdot4\cdot3\cdot2\cdot1}-10$$| 1277 | 7,642 |

</details>

All 7,642 hands are stored in an unordered_map<string, int> where the key is a 6 character string and the value is 0 - 7,641 (Royal Flush - 7,5,4,3,2)

The only public function hand_rank(string) takes in a 6 character string and returns the hand's rank
```c++
int rank = hand_rank("22J94P");
cout << rank << endl;
>>6112

String Key:
- Cards sorted by priotity, then value
- Last character represents hand type
  - "22J94P" -> Pair of 2s
  - "AJ739F" -> Flush Ace High
  - "JJ77K+" -> 2 pairs Jacks & 7s, high card King

Hash Map: 
- "AKQJTR" = 0     - Royal Flush
- "75432C" = 7,641 - 7,5,4,3,2 off suit

## Installation & Running


## Implimentation

### Uses

