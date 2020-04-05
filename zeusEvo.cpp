#include <cstdlib>
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

const int TRIALS = 1000000;

int getzeus();
bool countZeus(int array[], int size, int target_dmg);

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    for(int target_dmg = 10; target_dmg <= 20; target_dmg+=2)
    {
        cout << "Over " << target_dmg
             << " damage with Zeus (" << TRIALS << " trials)" <<endl;

        for(int evo = 1; evo <= 20; ++evo)
        {
            int zeusCount = 0;
            for(int trial = 0; trial < TRIALS; ++trial)
            {
                int zeusEffect[evo];
                for(int ele = 0; ele < evo; ++ele)
                {
                    zeusEffect[ele] = getzeus();
                }

                if(countZeus(zeusEffect, evo, target_dmg))
                {
                    ++zeusCount;
                }
            }
            if(zeusCount > 0)
            {
                cout << "Evolved " << setw(2) << evo << " times: "
                     << static_cast<double>(zeusCount)/TRIALS * 100 << '%' << endl;
            }
        }
    }
}

int getzeus()
{
    return rand()%5;
}

bool countZeus(int array[], int size, int target_dmg)
{
    int dmgCount = 5;
    bool storm = false;
    for(int index = 0; index < size; ++index)
    {
        switch(array[index])
        {
        case 0:
            dmgCount += 2;
            storm = true;
            break;
        case 1:
            dmgCount += 3;
            break;
        case 2:
            ++dmgCount;
            break;
        case 3:
        default:
            break;
        }
    }

    return (dmgCount >= target_dmg && storm);
}
