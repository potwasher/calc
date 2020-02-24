#include <cstdlib>
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

const int TRIALS = 100000;
const int TARGET_DMG = 20;

int getzeus();
bool countZeus(int array[], int size);

int main(){
    srand(static_cast<unsigned int>(time(nullptr)));
    
    cout << "Over " << TARGET_DMG
         << " damage with Zeus (" << TRIALS << " trials)" <<endl;
    
    for(int evo = 1; evo <= 20; ++evo)
    {
        int zeusCount = 0;
        for(int trial = 0; trial < TRIALS; ++trial)
        {
            int zeusEffect[evo];
            for(int ele = 0; ele < evo; ++ele){
                zeusEffect[ele] = getzeus();
            }
            
            if(countZeus(zeusEffect, evo)){
                ++zeusCount;
            }
        }
        if(zeusCount > 0){
            cout << "Evolved " << setw(2) << evo << " times: "
            << zeusCount << endl;
        }
    }
}

int getzeus(){
    return rand()%5;
}

bool countZeus(int array[], int size){
    int dmgCount = 5;
    bool storm = false;
    for(int index = 0; index < size; ++index)
    {
        switch(array[index]){
            case 1: dmgCount += 2;
                    storm = true;
                    break;
            case 2: dmgCount += 3;
                    break;
            case 3: ++dmgCount;
                    break;
            case 4:
            default: break;
        }
    }
    
    if(dmgCount >= TARGET_DMG && storm)
    {
        return true;
    }
    else
    {
        return false;
    }
}
