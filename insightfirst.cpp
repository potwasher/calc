#include <algorithm>
#include <random>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>


using namespace std;


int main ()
{
    int TRIALS = 10000000;
    int kuon = 0;
    int mull_kuon = 0;
    int insight_kuon = 0;
    srand(static_cast<unsigned int>(time(nullptr)));

    for(int i = 0; i < TRIALS; ++i)
    {
        //bool hasKuon = false;
        vector<int> deck;

        //40 cards in deck vector
        for (int j=0; j<40; ++j)
        {
            deck.push_back(j+1);
        }

        //kuon = 38, 39, 40
        //insight = 1, 36, 37
        //guarantee 1 insight, A and B NOT insight or kuon
        //mull A,B, insight
        random_shuffle(deck.begin()+3, deck.end());
        //return 1-3 to the back of the deck
        for(int mull = 0; mull < 3; ++mull)
        {
            deck.push_back(deck.at(mull));
        }
        //erase 0-2
        deck.erase(deck.begin(), deck.begin()+3);

        //shuffle rest of deck before drawing post-mull cards
        random_shuffle(deck.begin()+3, deck.end());

        if(deck.at(0) >= 38
                or deck.at(1) >= 38
                or deck.at(2) >= 38)
        {
            ++kuon;
            ++mull_kuon;
            if(deck.at(0) == 1
                    or deck.at(0) == 36
                    or deck.at(0) == 37
                    or deck.at(1) == 1
                    or deck.at(1) == 36
                    or deck.at(1) == 37
                    or deck.at(2) == 1
                    or deck.at(2) == 36
                    or deck.at(2) == 37
                    or deck.at(3) == 1
                    or deck.at(3) == 36
                    or deck.at(3) == 37
               ){
                ++insight_kuon;
               }
            //hasKuon = true;
        }
        else
        {


            //0-2 are random cards drawn in mull, 3-39 are random cards drawn after mull

            if(deck.at(0) == 1
                    or deck.at(0) == 36
                    or deck.at(0) == 37
                    or deck.at(1) == 1
                    or deck.at(1) == 36
                    or deck.at(1) == 37
                    or deck.at(2) == 1
                    or deck.at(2) == 36
                    or deck.at(2) == 37
                    or deck.at(3) == 1
                    or deck.at(3) == 36
                    or deck.at(3) == 37
              )
            {
                if(deck.at(3) >= 38
                        or deck.at(4) >= 38
                        or deck.at(5) >= 38)
                {
                    ++kuon;
                    ++insight_kuon;
                    //hasKuon = true;
                }

            }
            else if(deck.at(3) >= 38
                    or deck.at(4) >= 38)
            {
                ++kuon;
                //hasKuon = true;
            }

        }
        /*if(hasKuon)
        {
            for(int print = 0; print < 10; ++print)
            {
                if(deck.at(print)>=38)
                {
                    cout << "Kuon ";
                }
                else
                {
                    cout << deck.at(print) << ' ';
                }

            }
            cout << endl;
        }*/
    }
    cout << "2t kuon: " << kuon << endl;
    cout << "kuon in mull: " << mull_kuon << endl;
    cout << "insight + kuon: " << insight_kuon << endl;


    return 0;
}Insight Insanity: 知恵の光を終わらせる part 1 特定のカードを一枚引く確率



