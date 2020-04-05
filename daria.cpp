#include <algorithm>
#include <iomanip>
#include <random>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

//15-25
// int NON_SPELLBOOST = 15;
int DECKSIZE = 39;
int TRIALS = 1000000;
int MAX_DRAW = 4;

int main(){
  //how many cards will be drawn off of Daria?
srand(time(nullptr));
  for(int non_spellboost = 15; non_spellboost <= 25; ++non_spellboost){
    vector<bool> deck;
    for(int card = 0; card < non_spellboost; ++card){
      deck.push_back(0);
    }
    for(int card = non_spellboost; card < DECKSIZE; ++card){
      deck.push_back(1);
    }

    int total_draw = 0;
    int drew2 = 0;
    int drew3 = 0;
    for(int trial = 0; trial < TRIALS; ++trial){
      random_shuffle(deck.begin(), deck.end());
      int draw  = 0;
      while(deck[draw] == 1 && draw < (MAX_DRAW-1)){
        ++draw;
      }
      if (draw >= 1){
        ++drew2;
        if(draw >= 2){
          ++drew3;
        }
      }
      total_draw += (draw + 1);
      // cout << draw << endl;
    }
    cout << non_spellboost << " non-spellboost: ";
     cout << static_cast<double>(total_draw) / TRIALS
         << ' '
         << static_cast<double>(drew2) / TRIALS * 100 << '%'
         << ' '
         << static_cast<double>(drew3) / TRIALS * 100 << '%'
         << endl;
  }
}
