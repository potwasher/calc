#include <random>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int numFairies(int cardNum, int draw);
int numFairies(vector<int> deck);
//void swap(int* a, int* b);
const int FIRSTSECOND = 1;
const int TARGET_TURN = 4;
const int TRIALS = 100000;

int main(){
    random_device r;
    seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    mt19937 eng(seed);

    //int to count
    int drewAmataz = 0;
    int haveFairy = 0;
    int haveSmith = 0;
    int noFairyHaveSmith = 0;

    for(int trial = 0; trial < TRIALS; ++trial){
        vector<int> deck;
        //40 cards in deck vector
        for (int j=0; j<40; ++j)
        {
            deck.push_back(j+1);
        }

        //pre-mulligan
        shuffle(deck.begin(), deck.end(), eng);

        //check pre-mulligan for mischievous, amataz
        bool amat[3] = {0};
        bool mischievous[3] = {0};
        for(int draw = 0; draw < 3; ++draw){
            if(deck[draw] == 31
               or deck[draw] == 32
               or deck[draw] == 33)
            {
                amat[draw] = true;
            }
            if(deck[draw] == 37
               or deck[draw] == 38
               or deck[draw] == 39)
            {
                mischievous[draw] = true;
            }
        }

        //determine post-mull cards
        shuffle(deck.begin()+3, deck.end(), eng);

        //mulligan
        if(amat[0]){
            amat[1]=0;
            amat[2]=0;
        } else if (amat[1]){
            amat[2]=0;
        }
        if(mischievous[0]){
            mischievous[1]=0;
            mischievous[2]=0;
        } else if (mischievous[1]){
            mischievous[2]=0;
        }
        bool dontMull[3] = {0};
        for(int i=0; i<3; ++i){
            if(amat[i]==true
               or mischievous[i]==true){
                dontMull[i]=true;
            }
            if(!dontMull[i]){
                swap(deck[i],deck[i+3]);
            }
        }


        //mulligan ended
        //random_shuffle(deck.begin()+3, deck.end());
        shuffle(deck.begin()+3, deck.end(), eng);

        //check if amataz is in hand
        bool haveAmataz = false;
        for(int draw = 0; draw < TARGET_TURN + FIRSTSECOND + 2; ++draw){
            if(deck[draw] == 31
               or deck[draw] == 32
               or deck[draw] == 33
               ){
                haveAmataz = true;
            }
        }
        if(haveAmataz == true){
            ++drewAmataz;
            if (numFairies(deck) >= 6){
                ++haveFairy;
            } else {
                bool smith = false;
                for(int draw = 0; draw < TARGET_TURN + FIRSTSECOND + 2; ++draw)
                {
                    if(deck[draw] == 9
                       or deck[draw] == 10
                       or deck[draw] == 11){
                        smith = true;
                    }
                }
                if(smith == true){
                    ++noFairyHaveSmith;;
                }
                
            }
        }
        else
        {
            bool smith = false;
            for(int draw = 0; draw < TARGET_TURN + FIRSTSECOND + 2; ++draw){

                if(deck[draw] == 9
                   or deck[draw] == 10
                   or deck[draw] == 11){
                    smith = true;
                }
            }
            if(smith == true){
                ++haveSmith;
            }
        }
    }
    if(FIRSTSECOND == 1){
        cout << "Going first" << endl;
    } else {
        cout << "Going second" << endl;
    }

    cout << "Drew amataz: "
    << setw(30) << drewAmataz << " times" << endl
    << "Had fairy gen w/ by turn " << TARGET_TURN << ':'
    << setw(16) << haveFairy << " times" << endl;
    cout << "smithing: " << haveSmith << endl;
    cout << "smithing + amataz complete:      "
         << haveFairy + noFairyHaveSmith + haveSmith << endl;
    cout << "smithing or amataz:      "
         << drewAmataz + haveSmith << endl << endl;
}

int numFairies(int cardNum, int draw){
    switch (cardNum) {
        case 0:
        case 1:
        case 2:
        case 21:
        case 22:
        case 23:
        case 27:
        case 28:
        case 29:
            return 1;
            break;
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
            return 2;
            break;
        case 37:
        case 38:
        case 39:
            //mmm,1,1,2,3,4
            // ex. turn 4 1st, up to card 7
            if(FIRSTSECOND == 1) {
                if(draw < 7) return 3;
                else return 2;
            } else {
                if(draw < 8) return 3;
                else return 2;
            }
            break;
        default:
            return 0;
    }
}

int numFairies(vector<int> deck){
    int totalFairies = 0;
    for(int draw = 0; draw < (TARGET_TURN + FIRSTSECOND + 2); ++draw){
        totalFairies += numFairies(deck[draw], draw);
    }
    return totalFairies;
}
