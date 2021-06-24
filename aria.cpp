#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>

using namespace std;

const int ARIA_COUNT = 3;
const int COUNT = 1000000;
const int DECK_MAX = 40;
const bool DEBUG = false;
const bool OUTPUT2 = true;

int insightCount;
int decksize;
int useInsight = 0;
int success = 0, insightUsed = 0;
int fail = 0;

bool foundAria(){
    int num = (rand() % decksize);
    if(DEBUG){
        cout << num << ' ' << decksize << endl;
    }
    if(num < ARIA_COUNT) return true;
    if(num < ARIA_COUNT+insightCount) {
        --insightCount;
        --decksize;
        useInsight++;
        return foundAria();
    }
    return false;
}

bool foundJustAria(){
    int num = (rand() % decksize);
    if(DEBUG){
        cout << num << ' ' << decksize << endl;
    }
    return num < ARIA_COUNT;
}

int main(){
    srand(time(nullptr));
    for(int insight = 0; insight <=9; insight++){
        for(int tests = 0; tests < COUNT; tests++){
            insightCount = insight;
            int drawsLeft = 3;
            decksize = DECK_MAX;
            bool ok = false;
            useInsight = 0;
            // mulligan
            while(drawsLeft--){
                if(foundJustAria()) {
                    ok = true;
                    break;
                }
                --decksize;
            }
            // post mulligan
            if(!ok){
                drawsLeft = 3;
                decksize = DECK_MAX - 3;
                while(drawsLeft--){
                    if(foundAria()) {
                        ok = true;
                        break;
                    }
                    --decksize;
                }
            }
            // reg draw
            if(!ok){
                drawsLeft = 4;
                decksize = DECK_MAX - 3 - useInsight;
                while(drawsLeft--){
                    if(foundAria()){
                        ok = true;
                        break;
                    }
                    --decksize;
                }
            }
            // first evo turn top deck
            if(!ok){
                if(foundJustAria()) ok = true;
            }
            if(ok){
                if(useInsight) insightUsed++;
                success++;
            } else {
                fail++;
            }
        }
        if(OUTPUT2){
            cout << fixed << setprecision(2) << (double) success / COUNT * 100 << "%" << endl;
        } else {
            cout << "Insight count: " << insight << endl;
            cout << "Sample size: " << COUNT << endl
                << "Aria found before evo turn: " << success << endl
                // << "Insight used to find Aria: " << insightUsed << endl
                << "fail: " << fail << endl;
            cout << fixed << setprecision(2) << (double) success / COUNT * 100 << "%" << endl << endl;
        }
        success = insightUsed = fail = 0;
    }
    return 0;
}
