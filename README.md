# Monte Carlo Poker

Monte Carlo Simulation for Texas Holdem Poker


## Overview

### Monte Carlo Simulation

The Monte Carlo Simulation runs n games determining winners based on best hand

### Hand Evaluator

The HandEval class defined in hand_eval.h & hand_eval.cpp evaluates a 5 - 7 card hand and determines the best hand. This is achieved primarily through algorithms using hashmaps.


The public 
```c++
>>> std::string best_hand(std::vector<Card*>& cards);
```

### Database

There are MM unique 5 card poker hands. However, there are only 7,642 different strengths of hands, as demonstrated below.


The TexasHoldemKey class defined in tx_hold_key.h & tx_hold_key.cpp creates a hash map of the 7,642 unique hands(key) and ranks(value) them from 0 (Royal Flush) to 7,641 (7,5,4,3,2).


The public function int hand_rank(std::sting hand) takes in a 6 character string and returns the hand's rank


## Installation & Running

```
$ pip install deuces
```

## Implimentation

### Uses

