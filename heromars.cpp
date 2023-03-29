#include <bits/stdc++.h>

#define TRIALS 1e6
#define first 0 // SET FIRST/SECOND
#define kat 2 // SET KATZE COUNT
#define CARDS 7

using namespace std;

enum CARD {
    BUMPKIN,
    REPORT,
    TONY,
    METATRON,
    MARS,
    KATZE,
    VALIANT,
};

int decksize = 40;
vector<int> rem, have;
int mars_first_evo = 0, mars_second_evo = 0;
int second_evo_only = 0;
int drew_valiant = 0;

// report = 3, metatron = 3, mars = 3, valiant = 1;
// bumpkin = 3, tony = 3, katze = 2;
void init() {
    decksize = 40;
    rem.clear(), have.clear();
    rem = vector<int>(CARDS, 3);
    rem[VALIANT] = 1, rem[KATZE] = kat;
    have = vector<int>(CARDS, 0);
}

int getOfficerCnt() {
    return decksize - (rem[REPORT] + rem[METATRON] + rem[MARS] + rem[VALIANT]);
}

void drawCommander() {
    int v = rem[VALIANT];
    int m = rem[MARS];
    int r = rand() % (v + m);
    if (r < m) {
        rem[MARS]--;
        have[MARS]++;
    } else {
        rem[VALIANT]--;
        have[VALIANT]++;
    }
    decksize--;
}

int draw() {
    int card = rand() % decksize;
    int sum = 0;
    int drawn = -1;
    for (int i = 0; i < (int)rem.size(); i++) {
        sum += rem[i];
        if (card < sum) {
            rem[i]--;
            drawn = i;
            break;
        }
    }
    decksize--;
    if (drawn == -1) {
        return -1;
    }
    have[drawn]++;
    return drawn;
}

void mulligan() {
    vector<int> replaced;
    for (int i = 0; i < 3; i++) {
        int d = draw();
        if (d == TONY || d == MARS) {
            continue;
        }
        replaced.push_back(d);
    }

    // keep tony, mars
    int tony_mars = have[TONY] + have[MARS];
    for (int i = 0; i < (3 - tony_mars); i++) {
        draw();
    }

    for (int i : replaced) {
        decksize++;
        if (i == -1) continue;
        rem[i]++;
        have[i]--;
    }
}

void trial() {
    init();

    // mull
    mulligan();
    // assert(decksize == 37);

    // t1: draw 4 or 5 depending on first/second
    for (int i = 0; i < (1 + !first); i++) {
        draw();
    }
    if (have[BUMPKIN] > 0) {
        have[BUMPKIN]--;
        draw();
    }

    // t2: draw 1, except bumpkin or tony
    draw();
    if (have[TONY] > 0) {
        have[TONY]--;
        drawCommander();
    } else if (have[BUMPKIN] > 0) {
        have[BUMPKIN]--;
        draw();
    }

    // t3: draw 1, except katze, bumpkin, tony
    draw();
    if (have[MARS] == 0) {
        if (have[TONY] > 0) {
            have[TONY]--;
            drawCommander();
        }
        if (have[BUMPKIN] > 0) {
            draw();
        }
    } else if (have[KATZE] > 0 && rem[VALIANT] > 0) {
        have[KATZE]--;
        rem[VALIANT]--;
        have[VALIANT]++;
        decksize--;
    } else {
        if (have[TONY] > 0 && rem[MARS] > 0) {
            have[TONY]--;
            drawCommander();
        } else if (have[BUMPKIN] > 0) {
            have[BUMPKIN]--;
            draw();
        }
        if (have[BUMPKIN] > 0) {
            have[BUMPKIN]--;
            draw();
        }
    }

    // t4
    bool mars1 = false;
    draw();
    if (!first) {
        if (have[MARS] > 0 && getOfficerCnt() >= 20) {
            mars1 = true;
            have[MARS]--;
        } else {
            if (have[TONY] > 0) {
                have[TONY]--;
                drawCommander();
            } else if (have[KATZE] > 0 && rem[VALIANT] > 0) {
                have[KATZE]--;
                rem[VALIANT]--;
                have[VALIANT]++;
                decksize--;
            }
            if (have[TONY] > 0) {
                have[TONY]--;
                drawCommander();
            }
        }
        if (have[BUMPKIN] > 0) {
            have[BUMPKIN]--;
            draw();
        }
    } else {
        draw();
        if (have[TONY] > 0 && rem[MARS] > 0) {
            have[TONY]--;
            drawCommander();
        } else {
            if (have[KATZE] > 0 && rem[VALIANT] > 0) {
                have[KATZE]--;
                rem[VALIANT]--;
                have[VALIANT]++;
                decksize--;
            } else if (have[BUMPKIN] > 0) {
                have[BUMPKIN]--;
                draw();
            }
        }
    }

    // t5
    bool mars2 = false;
    draw();
    if (first) {
        if (have[TONY] > 0) {
            have[TONY]--;
            drawCommander();
        }
        if (have[MARS] > 0 && getOfficerCnt() >= 20) {
            mars1 = true;
            have[MARS]--;
        }
    } else {
        if (have[TONY] > 0) {
            have[TONY]--;
            drawCommander();
        }
        if (have[MARS] > 0 && getOfficerCnt() >= 20) {
            mars2 = true;
            have[MARS]--;
        }
    }

    // t6
    draw();
    if (first) {
        if (have[TONY] > 0) {
            have[TONY]--;
            drawCommander();
        }
        if (have[MARS] > 0) {
            mars2 = true;
        }
    } else {
        if (have[KATZE] > 0 && rem[VALIANT] > 0) {
            have[KATZE]--;
            rem[VALIANT]--;
            have[VALIANT]++;
            decksize--;
        }
        if (have[TONY] > 0) {
            have[TONY]--;
            drawCommander();
        }
    }

    // t7
    draw();

    if (mars1) {
        mars_first_evo++;
    }
    if (mars2) {
        if (mars1) {
            mars_second_evo++;
        } else {
            second_evo_only++;
        }
    }
    if (have[VALIANT] > 0) {
        drew_valiant++;
    }
}

int main() {
    srand(time(nullptr));
    for (int t = 0; t < TRIALS; t++) {
        trial();
    }
    cout << mars_first_evo << ' ' << mars_second_evo << ' ' << second_evo_only << "\n\n";

    cout << setprecision(2) << fixed;
    cout << "mars on first evo: " << (mars_first_evo / TRIALS) << "%\n"
        << "mars also on second evo: " << (mars_second_evo / TRIALS) << "%\n"
        << "mars only on second evo: " << (second_evo_only / TRIALS) << "%\n"
        << "no mars: " << ((TRIALS - mars_first_evo - second_evo_only) / TRIALS) << "%\n"
        << "fencer: " << (drew_valiant / TRIALS) << "%\n";
}
