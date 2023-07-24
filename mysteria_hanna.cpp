#include <bits/stdc++.h>
using namespace std;
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

const int TEST = int(1e6);
bool FIRST = true;
int set_hanna = 1, set_gratitude = 2, set_missile = 8;

int decksz;
int rem[10], curr[10];
int t4founder_annegrea = 0, founder_annegrea = 0, found3 = 0, found4 = 0;

enum CARD {
    founder,     // myst
    annegrea,    // myst
    craig,       // myst
    hanna,       // myst
    freyja,
    party,       // acad, myst
    gratitude,   // acad
    instruction, // acad, myst
    insight,
    missile,
};

void init() {
    rem[founder] = 1, rem[annegrea] = 1, rem[craig] = 1, rem[hanna] = set_hanna;
    rem[freyja] = 3, rem[gratitude] = set_gratitude;
    rem[instruction] = 3, rem[party] = 3;
    rem[insight] = 3, rem[missile] = set_missile;
    memset(curr, 0, sizeof(curr));
    decksz = 40;
}

int draw() {
    decksz--;
    int card = uid(0, decksz);
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        if (rem[i] == 0) continue;
        sum += rem[i];
        if (card < sum) {
            rem[i]--;
            curr[i]++;
            return i;
        }
    }
    return -1;
}

void draw_mysteria() {
    decksz--;
    int sum = 0;
    for (int i = 0; i <= hanna; i++) {
        sum += rem[i];
    }
    int card = uid(0, sum - 1);
    sum = 0;
    for (int i = 0; i <= hanna; i++) {
        if (rem[i] == 0) continue;
        sum += rem[i];
        if (card < sum) {
            rem[i]--;
            curr[i]++;
            return;
        }
    }
}

int draw_gratitude() {
    int academic_drawn = 0;
    for (int i = 0; i < 2; i++) {
        decksz--;
        int card = uid(0, decksz);
        int sum = 0;
        for (int j = 0; j < 10; j++) {
            if (rem[i] == 0) continue;
            sum += rem[j];
            if (card < sum) {
                rem[j]--;
                curr[j]++;
                if (j >= party && j <= instruction) {
                    academic_drawn++;
                }
                break;
            }
        }
    }
    return academic_drawn;
}

void runFirst() {
    init();
    // mulligan
    vector<int> redraw;
    int mull_grat = 0;
    for (int i = 0; i < 3; i++) {
        redraw.push_back(draw());
        if (redraw.back() != -1
            && redraw.back() <= gratitude) {
            redraw.pop_back();
        } else if (redraw.back() == gratitude) {
            if (curr[gratitude] - mull_grat > 1) {
                mull_grat++;
            } else {
                redraw.pop_back();
            }
        }
    }
    for (int i = 0; i < (int)redraw.size(); i++) {
        draw();
    }
    for (int i : redraw) {
        decksz++;
        if (i != -1) {
            curr[i]--;
            rem[i]++;
        }
    }
    assert(decksz == 37);

    // t1
    draw();
    if (curr[insight] > 0) {
        curr[insight]--;
        draw();
    } else if (curr[party] > 0) {
        curr[party]--;
        draw_mysteria();
    }

    // t2
    {
        draw();
        // if (curr[gratitude] > 0) {
        if (curr[freyja] + curr[hanna] >= 2
            || (curr[founder] + curr[annegrea] + curr[craig] > 1)) {
            if (curr[freyja] > 0) {
                curr[freyja]--;
                draw_mysteria();
            } else if (curr[hanna] > 0) {
                curr[hanna]--;
                draw_mysteria();
            } else if (curr[missile] > 0) {
                curr[missile]--;
                draw();
            } else {
                for (int i = 0; i < 2; i++) {
                    if (curr[insight] > 0) {
                        curr[insight]--;
                        draw();
                    } else if (curr[party] > 0) {
                        curr[party]--;
                        draw_mysteria();
                    }
                }
            }
        } else {
            if (curr[missile] > 0) {
                curr[missile]--;
                draw();
            } else if (curr[freyja] > 0) {
                curr[freyja]--;
                draw_mysteria();
            } else if (curr[hanna] > 0) {
                curr[hanna]--;
                draw_mysteria();
            } else {
                for (int i = 0; i < 2; i++) {
                    if (curr[insight] > 0) {
                        curr[insight]--;
                        draw();
                    } else if (curr[party] > 0) {
                        curr[party]--;
                        draw_mysteria();
                    }
                }
            }
        }
    }

    // t3
    {
        draw();
        int pp = 3;
        bool end = false;
        while (pp > 0 && !end) {
            end = true;
            if (pp >= 3 && curr[gratitude] > 0) {
                curr[gratitude]--;
                pp -= (3 - draw_gratitude());
                end = false;
            } else if (pp >= 2 && curr[freyja] > 0) {
                curr[freyja]--;
                pp -= 2;
                draw_mysteria();
                end = false;
            } else if (pp >= 2 && curr[hanna] > 0) {
                curr[hanna]--;
                pp -= 2;
                draw_mysteria();
                end = false;
            } else if (pp >= 1 && curr[party] > 0) {
                curr[party]--;
                pp--;
                draw_mysteria();
                end = false;
            } else if (pp >= 1 && curr[insight] > 0) {
                curr[insight]--;
                pp--;
                draw();
                end = false;
            } else if (pp >= 2 && curr[missile] > 0) {
                curr[missile]--;
                pp -= 2;
                draw();
                end = false;
            }
        }
    }

    // t4
    {
        draw();
        int pp = 4;
        bool end = false;
        while (pp > 0 && !end) {
            end = true;
            if (pp >= 2 && curr[freyja] > 0) {
                curr[freyja]--;
                draw_mysteria();
                pp -= 2;
                end = false;
            } else if (pp >= 2 && curr[hanna] > 0) {
                curr[hanna]--;
                draw_mysteria();
                pp -= 2;
                end = false;
            } else if (pp >= 3 && curr[gratitude] > 0) {
                curr[gratitude]--;
                pp -= (3 - draw_gratitude());
                end = false;
            } else if (pp >= 1 && curr[party] > 0) {
                curr[party]--;
                pp--;
                draw_mysteria();
                end = false;
            } else if (pp >= 1 && curr[insight] > 0) {
                curr[insight]--;
                pp--;
                draw();
                end = false;
            } else if (pp >= 2 && curr[missile] > 0) {
                curr[missile]--;
                pp -= 2;
                draw();
                end = false;
            }
        }
    }

    // t5
    draw();
    bool found_ann = (rem[annegrea] == 0);
    // t6
    draw();
    if (rem[founder] == 0 && found_ann) {
        founder_annegrea++;
        if (rem[craig] == 0) {
            found3++;
            if (rem[hanna] == 0) found4++;
        }
    }
}

void runSecond() {
    init();
    // mulligan
    vector<int> redraw;
    int mull_grat = 0;
    for (int i = 0; i < 3; i++) {
        redraw.push_back(draw());
        if (redraw.back() != -1
            && redraw.back() < gratitude) {
            redraw.pop_back();
        } else if (redraw.back() == gratitude) {
            if (curr[gratitude] - mull_grat > 1) {
                mull_grat++;
            } else {
                redraw.pop_back();
            }
        }
    }
    for (int i = 0; i < (int)redraw.size(); i++) {
        draw();
    }
    for (int i : redraw) {
        decksz++;
        if (i != -1) {
            curr[i]--;
            rem[i]++;
        }
    }
    assert(decksz == 37);

    // t1
    draw();
    draw();
    if (curr[insight] > 0) {
        curr[insight]--;
        draw();
    } else if (curr[party] > 0) {
        curr[party]--;
        draw_mysteria();
    }

    // t2
    {
        draw();
        if (curr[hanna] > 0) {
            curr[hanna]--;
            draw_mysteria();
        } else if (curr[freyja] > 0) {
            curr[freyja]--;
            draw_mysteria();
        } else if (curr[missile] > 0) {
            curr[missile]--;
            draw();
        } else {
            for (int i = 0; i < 2; i++) {
                if (curr[insight] > 0) {
                    curr[insight]--;
                    draw();
                } else if (curr[party] > 0) {
                    curr[party]--;
                    draw_mysteria();
                }
            }
        }
    }

    // t3
    {
        draw();
        int pp = 3;
        bool end = false;
        if (curr[founder] > 0) {
            while (pp > 0 && !end) {
                end = true;
                if (pp >= 3 && curr[gratitude] > 0) {
                    curr[gratitude]--;
                    pp -= (3 - draw_gratitude());
                    end = false;
                } else if (pp >= 2 && curr[hanna] > 0) {
                    curr[hanna]--;
                    pp -= 2;
                    draw_mysteria();
                    end = false;
                } else if (pp >= 2 && curr[freyja] > 0) {
                    curr[freyja]--;
                    pp -= 2;
                    draw_mysteria();
                    end = false;
                } else if (pp >= 1 && curr[party] > 0) {
                    curr[party]--;
                    pp--;
                    draw_mysteria();
                    end = false;
                } else if (pp >= 1 && curr[insight] > 0) {
                    curr[insight]--;
                    pp--;
                    draw();
                    end = false;
                } else if (pp >= 2 && curr[missile] > 0) {
                    curr[missile]--;
                    pp -= 2;
                    draw();
                    end = false;
                }
            }
        } else {
            while (pp > 0 && !end) {
                end = true;
                if (pp >= 2 && curr[hanna] > 0) {
                    curr[hanna]--;
                    pp -= 2;
                    draw_mysteria();
                    end = false;
                } else if (pp >= 2 && curr[freyja] > 0) {
                    curr[freyja]--;
                    pp -= 2;
                    draw_mysteria();
                    end = false;
                } else if (pp >= 1 && curr[party] > 0) {
                    curr[party]--;
                    pp--;
                    draw_mysteria();
                    end = false;
                } else if (pp >= 3 && curr[gratitude] > 0) {
                    curr[gratitude]--;
                    pp -= (3 - draw_gratitude());
                    end = false;
                } else if (pp >= 1 && curr[insight] > 0) {
                    curr[insight]--;
                    pp--;
                    draw();
                    end = false;
                } else if (pp >= 2 && curr[missile] > 0) {
                    curr[missile]--;
                    pp -= 2;
                    draw();
                    end = false;
                }
            }
        }
    }

    bool t4founder = false;
    // t4
    {
        draw();
        int pp = 4;
        bool end = false;
        int down[10];
        while (pp > 0 && !end) {
            end = true;
            if (t4founder) {
                end = false;
                if (down[party] > 0) {
                    for (int i = 0; i < curr[party]; i++) {
                        draw_mysteria();
                    }
                    curr[party] = 0;
                    down[party] = 0;
                } else if (down[insight] > 0) {
                    for (int i = 0; i < curr[insight]; i++) {
                        curr[insight]--;
                        draw();
                    }
                    down[insight] = 0;
                } else if (pp >= 1 && curr[freyja] > 0) {
                    curr[freyja]--;
                    pp--;
                    draw_mysteria();
                } else if (pp >= 1 && down[hanna] > 0) {
                    down[hanna]--;
                    curr[hanna]--;
                    pp--;
                    draw_mysteria();
                } else if (pp >= 1 && down[missile] > 0) {
                    down[missile]--;
                    curr[missile]--;
                    pp--;
                    draw();
                } else {
                    end = true;
                    if (pp >= 1 && curr[freyja] > 0) {
                        curr[freyja]--;
                        draw_mysteria();
                        pp--;
                        end = false;
                    } else if (pp >= 2 && curr[hanna] > 0) {
                        curr[hanna]--;
                        draw_mysteria();
                        pp -= 2;
                        end = false;
                    } else if (pp >= 3 && curr[gratitude] > 0) {
                        curr[gratitude]--;
                        pp -= (3 - draw_gratitude());
                        end = false;
                    } else if (pp >= 1 && curr[party] > 0) {
                        curr[party]--;
                        pp--;
                        draw_mysteria();
                        end = false;
                    } else if (pp >= 1 && curr[insight] > 0) {
                        curr[insight]--;
                        pp--;
                        draw();
                        end = false;
                    } else if (pp >= 2 && curr[missile] > 0) {
                        curr[missile]--;
                        pp -= 2;
                        draw();
                        end = false;
                    }
                }
            } else if (pp >= 3 && curr[founder] > 0) {
                pp -= 3;
                t4founder = true;
                for (int i = 0; i < 10; i++) {
                    down[i] = curr[i];
                }
            } else if (pp >= 1 && curr[freyja] > 0) {
                curr[freyja]--;
                draw_mysteria();
                pp--;
                end = false;
            } else if (pp >= 2 && curr[hanna] > 0) {
                curr[hanna]--;
                draw_mysteria();
                pp -= 2;
                end = false;
            } else if (pp >= 3 && curr[gratitude] > 0) {
                curr[gratitude]--;
                pp -= (3 - draw_gratitude());
                end = false;
            } else if (pp >= 1 && curr[party] > 0) {
                curr[party]--;
                pp--;
                draw_mysteria();
                end = false;
            } else if (pp >= 1 && curr[insight] > 0) {
                curr[insight]--;
                pp--;
                draw();
                end = false;
            } else if (pp >= 2 && curr[missile] > 0) {
                curr[missile]--;
                pp -= 2;
                draw();
                end = false;
            }
        }
    }

    // t5
    draw();
    bool found_ann = (rem[annegrea] == 0);
    if (found_ann && t4founder) {
        t4founder_annegrea++;
    }
    // t6
    draw();
    if (rem[founder] == 0 && found_ann) {
        founder_annegrea++;
        if (rem[craig] == 0) {
            found3++;
            if (rem[hanna] == 0) found4++;
        }
    }
}

int main() {
    if (FIRST) {
        for (int t = 0; t < TEST; t++) {
            runFirst();
        }
        cout << fixed << setprecision(2)
            << "Anne-Grea + Founder: " << founder_annegrea * 100 /
            (double)TEST
            << '\n'
            << "+ Craig: " << found3 * 100 / (double)TEST << '\n'
            << "Found 4: " << found4 * 100 / (double)TEST << '\n';
    } else {
        for (int t = 0; t < TEST; t++) {
            runSecond();
        }
        cout << fixed << setprecision(2)
            << "t4 Founder + Anne-Grea: " << t4founder_annegrea * 100 / (double)TEST
            << '\n'
            << "t5 Anne-Grea + Founder: " << founder_annegrea * 100 / (double)TEST
            << '\n'
            << "t6 Craig: " << found3 * 100 / (double)TEST << '\n'
            << "t6 Found 4: " << found4 * 100 / (double)TEST << '\n';
    }
}
