#include <bits/stdc++.h>
using namespace std;

int orchis_cnt = 3;
int pp1_pup1 = 6; // tinkering shopkeeper, young threadmaster
int pp2_pup1 = 6; // threadsnipper, inauspicious
int pp1_pup2 = 3; // craftsman's pride
int pp3_pup2 = 3; // licht
int ramiel_cnt = 3;

int found_orchis = 0, found_ramiel = 0;
int ramiel_orchis = 0, ramiel_orchis3 = 0, ramiel_orchis4 = 0;
int puppet_cnt_over3 = 0, puppet_cnt_over4 = 0;
int orchis_3puppet = 0, orchis_4puppet = 0;
int puppet_total = 0;

void reset() {
	found_orchis = 0, puppet_cnt_over3 = 0, puppet_cnt_over4 = 0, puppet_total = 0, orchis_3puppet = 0, orchis_4puppet = 0;
	found_ramiel = 0, ramiel_orchis = 0, ramiel_orchis3 = 0, ramiel_orchis4 = 0;
}

void run_second() {
	int decksize = 40;
	int draws = 7;
	int puppets = 0;
	int orchis = orchis_cnt, ramiel = ramiel_cnt;
	vector<int> cards = {
		pp1_pup1 + pp2_pup1,
		pp1_pup2 + pp3_pup2
	};

	// mulligan = keep orchis only
	vector<int> mull(3);
	int mull_redraw = 0;
	for (int i = 0; i < 3; i++) {
		mull[i] = rand() % decksize;
		decksize--;
	}
	if (*min_element(mull.begin(), mull.end()) >= orchis + ramiel) {
		mull_redraw += 3;
	} else {
		for (int i: mull) {
			if (i < orchis) {
				if (orchis < 3) {
					mull_redraw++;
				} else {
					orchis--;
				}
			} else if (i < orchis + ramiel) {
				if (ramiel < 3) {
					mull_redraw++;
				} else {
					ramiel--;
				}
			} else if (i < cards[0] + orchis + ramiel) {
				puppets++;
				cards[0]--;
			} else if (i < cards[1] + cards[0] + orchis + ramiel) {
				puppets += 2;
				cards[1]--;
			} else {
				mull_redraw++;
			}
		}
	}
	for (int i = 0; i < mull_redraw; i++) {
		int redraw = rand() % decksize;
		decksize--;
		if (redraw < orchis) {
			orchis--;
		} else if (redraw < orchis + ramiel) {
			ramiel--;
		} else if (redraw < orchis + ramiel + cards[0]) {
			puppets++;
			cards[0]--;
		} else if (redraw < orchis + ramiel + cards[0] + cards[1]) {
			puppets += 2;
			cards[1]--;
		}
	}
	decksize += 3;

	// draw
	for (int i = 0; i < 5; i++) {
		int draw = rand() % decksize;
		decksize--;
		if (draw < orchis) {
			orchis--;
		} else if (draw < orchis + ramiel) {
			ramiel--;
		} else if (draw < orchis + cards[0]) {
			puppets++;
			cards[0]--;
		} else if (draw < orchis + cards[0] + cards[1]) {
			puppets += 2;
			cards[1]--;
		}
	}
	draws -= 5;


	for (int i = 0; i < draws - 1; i++) {
		int draw = rand() % decksize;
		decksize--;
		if (draw < orchis) {
			orchis--;
		} else if (draw < orchis + cards[0]) {
			puppets++;
			cards[0]--;
		} else if (draw < orchis + cards[0] + cards[1]) {
			puppets += 2;
			cards[1]--;
		}
	}

	puppet_cnt_over3 += (puppets >= 3);
	puppet_cnt_over4 += (puppets >= 4);
	puppet_total += puppets;

	int lastdraw = rand() % decksize;
	if (lastdraw < orchis) {
		orchis--;
	}

	found_orchis += (orchis < 3);
	orchis_3puppet += (orchis < 3) && (puppets >= 3);
	orchis_4puppet += (orchis < 3) && (puppets >= 4);
	found_ramiel += (ramiel < 3);
	ramiel_orchis += (ramiel < 3) && (orchis < 3);
	ramiel_orchis3 += (ramiel < 3) && (orchis < 3) && (puppets >= 3);
	ramiel_orchis4 += (ramiel < 3) && (orchis < 3) && (puppets >= 4);
}

void run_first() {
	int decksize = 40;
	int draws = 6;
	int orchis = orchis_cnt;
	int puppets = 0;
	vector<int> cards = {
		pp1_pup1 + pp2_pup1,
		pp1_pup2 + pp3_pup2
	};

	// mulligan = keep orchis only
	vector<int> mull(3);
	int mull_redraw = 0;
	for (int i = 0; i < 3; i++) {
		mull[i] = rand() % decksize;
		decksize--;
	}
	if (*min_element(mull.begin(), mull.end()) >= orchis) {
		mull_redraw += 3;
	} else {
		for (int i: mull) {
			if (i < orchis) {
				if (orchis < 3) {
					mull_redraw++;
				} else {
					orchis--;
				}
			} else if (i < cards[0] + orchis) {
				puppets++;
				cards[0]--;
			} else if (i < cards[1] + cards[0] + orchis) {
				puppets += 2;
				cards[1]--;
			} else {
				mull_redraw++;
			}
		}
	}
	for (int i = 0; i < mull_redraw; i++) {
		int redraw = rand() % decksize;
		decksize--;
		if (redraw < orchis) {
			orchis--;
		} else if (redraw < orchis + cards[0]) {
			puppets++;
			cards[0]--;
		} else if (redraw < orchis + cards[0] + cards[1]) {
			puppets += 2;
			cards[1]--;
		}
	}
	decksize += 3;

	// draw
	for (int i = 0; i < draws - 1; i++) {
		int draw = rand() % decksize;
		decksize--;
		if (draw < orchis) {
			orchis--;
		} else if (draw < orchis + cards[0]) {
			puppets++;
			cards[0]--;
		} else if (draw < orchis + cards[0] + cards[1]) {
			puppets += 2;
			cards[1]--;
		}
	}

	puppet_cnt_over3 += (puppets >= 3);
	puppet_cnt_over4 += (puppets >= 4);
	puppet_total += puppets;

	int lastdraw = rand() % decksize;
	if (lastdraw < orchis) {
		orchis--;
	}

	found_orchis += (orchis < 3);
	orchis_3puppet += (orchis < 3) && (puppets >= 3);
	orchis_4puppet += (orchis < 3) && (puppets >= 4);
}

int main() {
	srand(time(nullptr));
	cout << setprecision(4);

	const int TRIAL = 1e6;
	for (int t = 0; t < TRIAL; t++) {
		run_first();
	}
	cout << "First:\n"
		 << "Found Orchis: " << (double)found_orchis / TRIAL << '\n'
		 << "3+ puppets: " << (double)puppet_cnt_over3 / TRIAL << '\n'
		 << "4+ puppets: " << (double)puppet_cnt_over4 / TRIAL << '\n'
		 << "Orchis + 3 puppets: " << (double)orchis_3puppet / TRIAL << '\n'
		 << "Orchis + 4 puppets: " << (double)orchis_4puppet / TRIAL << '\n'
		 << "Avg puppet cnt: " << (double)puppet_total / TRIAL << "\n\n";


	reset();
	for (int t = 0; t < TRIAL; t++) {
		run_second();
	}
	cout << "Second:\n"
		 << "Found Orchis: " << (double)found_orchis / TRIAL << '\n'
		 << "3+ puppets: " << (double)puppet_cnt_over3 / TRIAL << '\n'
		 << "4+ puppets: " << (double)puppet_cnt_over4 / TRIAL << '\n'
		 << "Orchis + 3 puppets: " << (double)orchis_3puppet / TRIAL << '\n'
		 << "Orchis + 4 puppets: " << (double)orchis_4puppet / TRIAL << '\n'
		 << "Ramiel Orchis: " << (double)ramiel_orchis / TRIAL << '\n'
		 << "Ramiel + Orchis + 3 puppets: " << (double)ramiel_orchis3 / TRIAL << '\n'
		 << "Ramiel + Orchis + 4 puppets: " << (double)ramiel_orchis4 / TRIAL << '\n'
		 << "Avg puppet cnt: " << (double)puppet_total / TRIAL << "\n\n";
}
