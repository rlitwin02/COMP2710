//author Ryan Litwin
//version 9/13/20
//Project 2, project2_Litwin_rpl0010.cpp
//compile using g++ project2_Litwin_rpl0010.cpp -0 a.out
//run ./a.out

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

//variables
//accuracy
const double aaronAccuracy = 0.3333333;
const double bobAccuracy = 0.5;
const double charlieAccuracy = 1;
//int for the amount of duels
const int totalDuels = 10000;

bool at_least_two_alive(bool aaronAlive, bool bobAlive, bool charlieAlive) {
    int allPlayersAlive = 0;
    allPlayersAlive = aaronAlive ? allPlayersAlive + 1 : allPlayersAlive;
    allPlayersAlive = bobAlive ? allPlayersAlive + 1 : allPlayersAlive;
    allPlayersAlive = charlieAlive ? allPlayersAlive + 1 : allPlayersAlive;
    
    return allPlayersAlive >= 2 ? true : false;
}

bool shoot(double accuracy) {
    double shootTarget = ((double) rand()) / (double) RAND_MAX;
    return shootTarget <= accuracy;
}

int Aaron_shoots1(bool& bobAlive, bool& charlieAlive) {
    if (charlieAlive) {
        bool hit = shoot(aaronAccuracy);
        charlieAlive = hit ? false : charlieAlive;
        return 2;
    }
    else if (bobAlive) {
        bool hit = shoot(aaronAccuracy);
        bobAlive = hit ? false : bobAlive;
        return 1;
    }
    return -1;
}

int Aaron_shoots2(bool& bobAlive, bool& charlieAlive) {
    if (bobAlive && charlieAlive) {
        return -1;
    }
    return Aaron_shoots1(bobAlive, charlieAlive);
}

int Bob_shoots(bool& aaronAlive, bool& charlieAlive) {
    if (charlieAlive) {
        bool hit = shoot(bobAccuracy);
        charlieAlive = hit ? false : charlieAlive;
        return 2;
    }
    else if (aaronAlive) {
        bool hit = shoot(bobAccuracy);
        aaronAlive = hit ? false : aaronAlive;
        return 0;
    }
    return -1;
}

int Charlie_shoots(bool& aaronAlive, bool& bobAlive) {
    if (bobAlive) {
        bool hit = shoot(charlieAccuracy);
        bobAlive = hit ? false : bobAlive;
        return 1;
    }
    else if (aaronAlive) {
        bool hit = shoot(charlieAccuracy);
        aaronAlive = hit ? false : aaronAlive;
        return 0;
    }
    return -1;
}

int duel(int strategy) {
    bool aaronAlive = true;
    bool bobAlive = true;
    bool charlieAlive = true;
    while (at_least_two_alive(aaronAlive, bobAlive, charlieAlive)) {
        if (aaronAlive) {
            if (strategy == 1) {
                Aaron_shoots1(bobAlive, charlieAlive);
            }
            else if (strategy == 2) {
                Aaron_shoots2(bobAlive, charlieAlive);
            }
        }
        if (bobAlive) {
            Bob_shoots(aaronAlive, charlieAlive);
        }
        if (charlieAlive) {
            Charlie_shoots(aaronAlive, bobAlive);
        }
    }
    return aaronAlive ? 0 : bobAlive ? 1 : charlieAlive ? 2 : -1;
}

// implementing the pause function
void Press_any_key(void) {
    cout << "Press any key to continue...";
    cin.ignore().get();
}

//testing at_least_two_alive
void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";
    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(at_least_two_alive(true, false, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(at_least_two_alive(true, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 5: Aaron dead, Bob dead, Charlie Alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\tCase passed ...\n";

    Press_any_key();
    
    
}
// testing Aaron_shoots1
void test_Aaron_shoots1(void) {
    cout << "Unit Testing 2: Function Aaron_shoots1(bobAlive, charlieAlive)\n";
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    bool bob = true; bool charlie = true;
    assert(2 == Aaron_shoots1(bob, charlie));
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    bob = false; charlie = true;
    assert(2 == Aaron_shoots1(bob, charlie));
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    bob = true; charlie = false;
    assert(1 == Aaron_shoots1(bob, charlie));
    cout << "\t\tAaron is shooting at Bob\n";

    Press_any_key();
}
// testing Bob_shoots
void test_Bob_shoots(void) {
    cout << "Unit Testing 3: Function Bob_shoots(aaronAlive, charlieAlive)\n";
    cout << "\tCase 1: Aaron alive, Charlie alive\n";
    bool aaron = true; bool charlie = true;
    assert(2 == Bob_shoots(aaron, charlie));
    cout << "\t\tBob is shooting at Charlie\n";

    cout << "\tCase 2: Aaron dead, Charlie alive\n";
    aaron = false; charlie = true;
    assert(2 == Bob_shoots(aaron, charlie));
    cout << "\t\tBob is shooting at Charlie\n";

    cout << "\tCase 3: Aaron alive, Charlie dead\n";
    aaron = true; charlie = false;
    assert(0 == Bob_shoots(aaron, charlie));
    cout << "\t\tBob is shooting at Aaron\n";

    Press_any_key();
}
// testing Charlie_shoots
void test_Charlie_shoots(void) {
    cout << "Unit Testing 4: Function Bob_shoots(aaronAlive, bobAlive)\n";
    cout << "\tCase 1: Aaron alive, Bob alive\n";
    bool aaron = true; bool bob = true;
    assert(1 == Charlie_shoots(aaron, bob));
    cout << "\t\tCharlie is shooting at Bob\n";

    cout << "\tCase 2: Aaron dead, Bob alive\n";
    aaron = false; bob = true;
    assert(1 == Charlie_shoots(aaron, bob));
    cout << "\t\tCharlie is shooting at Bob\n";

    cout << "\tCase 3: Aaron alive, Bob dead\n";
    aaron = true; bob = false;
    assert(0 == Charlie_shoots(aaron, bob));
    cout << "\t\tCharlie is shooting at Aaron\n";

    Press_any_key();
}
// testing Aaron_shoots2
void test_Aaron_shoots2(void) {
    cout << "Unit Testing 5: Function Aaron_shoots2(bobAlive, charlieAlive)\n";
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    bool bob = true; bool charlie = true;
    assert(-1 == Aaron_shoots2(bob, charlie));
    cout << "\t\tAaron intentionally misses his first shot\n";
    assert(bob == true); assert(charlie == true);
    cout << "\t\tBoth Bob and Charlie are alive\n";

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    bob = false; charlie = true;
    assert(2 == Aaron_shoots2(bob, charlie));
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    bob = true; charlie = false;
    assert(1 == Aaron_shoots2(bob, charlie));
    cout << "\t\tAaron is shooting at Bob\n";

    Press_any_key();
}
// testing for duel
int test_duel(int strategy) {
    cout << "Ready to test strategy " << strategy << " (run " << totalDuels << " times):\n";

    Press_any_key();

    int aaronWins = 0; int bobWins = 0; int charlieWins = 0;
    for (int i = 0; i < totalDuels; i++) {
        int duelResult = duel(strategy);
        switch (duelResult) {
            case 0: aaronWins++;
                break;
            case 1: bobWins++;
                break;
            case 2: charlieWins++;
                break;
        }
    }

    cout << "Aaron won " << aaronWins << "/" << totalDuels << " duels or " << static_cast <double>(aaronWins) / totalDuels * 100 << "%\n";
    cout << "Bob won " << bobWins << "/" << totalDuels << " duels or " << static_cast <double>(bobWins) / totalDuels * 100 << "&\n";
    cout << "Charlie won " << charlieWins << "/" << totalDuels << " duels or " << static_cast <double>(charlieWins) / totalDuels * 100 << "%\n";
    cout << endl;

    return aaronWins;
}
// says which strategy is more effective
void strategies(int wins1, int wins2) {
    if (wins1 > wins2) {
        cout << "Strategy 1 is better than strategy 2.";
    }
    else if (wins2 > wins1) {
        cout << "Strategy 2 is better than strategy 1.";
    }
    else {
        cout << "Strategy 1 is equal to strategy 2.";
    }
}
// main method
int main() {
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
// initializes rand
    srand(time(0));
    rand();

    cout << "*** Welcome to Ryan's Duel Simulator ***\n";
    test_at_least_two_alive();
    test_Aaron_shoots1();
    test_Bob_shoots();
    test_Charlie_shoots();
    test_Aaron_shoots2();

    int wins1 = test_duel(1);
    int wins2 = test_duel(2);
    strategies(wins1, wins2);

    cout << endl;
    return 0;
}