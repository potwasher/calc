#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void swap(int* a, int* b);
bool isKuon(int &card);
bool isInsight(int &card);

const bool KEEP_INSIGHT = false;
const int FIRSTSECOND = 2;
const int TARGET_TURN = 2;
const int NUM_TRIALS = 100000;

int main(){
    //random seed
    random_device r;
    seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    mt19937 eng(seed);

    unsigned int KuonCount = 0;

    for(int trial = 0; trial < NUM_TRIALS; ++trial){
        vector<int> deck;
        for(int index = 0; index < 40; ++index){
            deck.push_back(index);
        }

        // Insight + A + B,  A,B are non-Kuon non-Insight
        // 0, 3, 4,
        swap(deck[3], deck[1]);
        swap(deck[4], deck[2]);

        shuffle(deck.begin()+3, deck.end(), eng);

        if(!KEEP_INSIGHT){
            swap(deck[0], deck[3]);
            swap(deck[1], deck[4]);
            swap(deck[2], deck[5]);
        }
        else {
            swap(deck[1], deck[4]);
            swap(deck[2], deck[5]);
        }

        shuffle(deck.begin()+3, deck.end(), eng);

        int cards = FIRSTSECOND + TARGET_TURN + 2;

        if(FIRSTSECOND == 1){
            if(isInsight(deck[0]) or
               isInsight(deck[1]) or
               isInsight(deck[2]) or
               isInsight(deck[3])
               ){
            ++cards;
        }}
        else {
            if(isInsight(deck[0]) or
               isInsight(deck[1]) or
               isInsight(deck[2]) or
               isInsight(deck[3]) or
               isInsight(deck[4])
               ){
                ++cards;
            }
        }

        bool haveKuon = false;
        for(int index = 0; index < cards; ++index){
            if( isKuon( deck[index] ) ) {
                haveKuon = true;
            }
        }
        if(haveKuon) {
            ++KuonCount;
        }
    }

    if(KEEP_INSIGHT){
        cout << "keep insight" << endl;
    } else {
        cout << "toss insight" << endl;
    }

    cout << "trial count: " << NUM_TRIALS << endl;

    if(FIRSTSECOND==1){
        cout << "no of Kuon by turn " << TARGET_TURN << " going first" << endl;
    } else {
        cout << "no of Kuon by turn " << TARGET_TURN << " going second" << endl;
    }

    cout << KuonCount << endl;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool isKuon(int &card){
    switch(card){
        case 37:
        case 38:
        case 39: return true;
        default: return false;
    }
}

bool isInsight(int &card){
    switch(card){
        case 0:
        case 1:
        case 2: return true;
        default: return false;
    }
}



