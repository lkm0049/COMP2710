//Name: Liam Maher
//Date: 2/10/2020
//Assignment: COMP2710 Project 2
//userID: lkm0049
//filename: project2_Maher_lkm0049.cpp
//Compile: g++ project2_Maher_lkm0049.cpp -o Project2

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

//Shooting Accuracy Constants
const double A_accuracy = 0.3333333333;
const double B_accuracy = 0.5;
const double C_accuracy = 1.0;
//Total number of duels
const int total_duels = 10000;
//pause in code
void press_enter(void) {
    cout << "Press any key to continue...";
    cin.ignore().get();
}
//prototypes
//FUNCTION 1
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) { //This did not have bool in front of it on assignment sheet
    //number of players alive still
    int alive = 0;
    alive = A_alive ? alive + 1 : alive;
    alive = B_alive ? alive + 1 : alive;
    alive = C_alive ? alive + 1 : alive;
    return alive >= 2;
}
bool shoots_odds(double accuracy) {
    double shoot_target_result = ((double) rand()) / (double) RAND_MAX;
    return shoot_target_result <= accuracy;
}
/* Input: A_alive indicates whether Aaron is alive */
/* B_alive indicates whether Bob is alive */
/* C_alive indicates whether Charlie is alive */
/* Return: true if at least two are alive */
/* otherwise return false */
//FUNCTION 2
int Aaron_shoots1(bool& B_alive, bool& C_alive) {
    if (C_alive) {
        bool hit = shoots_odds(A_accuracy);
        C_alive = hit ? false : true;
        return 2;
    } else if (B_alive) {
        bool hit = shoots_odds(A_accuracy);
        B_alive = hit ? false : true;
        return 1;
    }
    return -1;
}
/* Strategy 1: Use call by reference
* Input: B_alive indicates whether Bob alive or dead
* C_alive indicates whether Charlie is alive or dead
* Return: Change B_alive into false if Bob is killed.
* Change C_alive into false if Charlie is killed.
*/
//FUNCTION 3
int Bob_shoots(bool& A_alive, bool& C_alive) {
    if (C_alive) {
        bool hit = shoots_odds(B_accuracy);
        C_alive = hit ? false : true;
        return 2;
    } else if (A_alive) {
        bool hit = shoots_odds(B_accuracy);
        A_alive = hit ? false : true;
        return 0;
    }
    return -1;
}
/* Call by reference
* Input: A_alive indicates if Aaron is alive or dead
* C_alive indicates whether Charlie is alive or dead
* Return: Change A_alive into false if Aaron is killed.
* Change C_alive into false if Charlie is killed.
*/
//FUNCTION 4
int Charlie_shoots(bool& A_alive, bool& B_alive) {
    if (B_alive) {
        bool hit = shoots_odds(C_accuracy);
        B_alive = hit ? false : true;
        return 1;
    } else if (A_alive) {
        bool hit = shoots_odds(C_accuracy);
        A_alive = hit ? false : true;
        return 0;
    }
    return -1;
}
/* Call by reference
* Input: A_alive indicates if Aaron is alive or dead
* B_alive indicates whether Bob is alive or dead
* Return: Change A_alive into false if Aaron is killed.
* Change B_alive into false if Bob is killed.
*/
//FUNCTION 5
int Aaron_shoots2(bool& B_alive, bool& C_alive) {
    if (C_alive && B_alive) {
        return -1;
    }
    return Aaron_shoots1(B_alive, C_alive);   
}
//TEST METHODS
//IF WONT COMPILE, CHECK THESE METHODS
void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";
    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n";
    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n";
    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\tCase passed ...\n";
    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\tCase passed ...\n";
    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
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
    press_enter();
}
void test_Aaron_shoots1(void) {
    cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
    bool B_alive = true;
    bool C_alive = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n\t\tAaron is shooting at Charlie\n";
    Aaron_shoots1(B_alive, C_alive);
    assert(true == B_alive);
    cout << "\tCase 2: Bob dead, Charlie alive\n\t\tAaron is shooting at Charlie\n";
    B_alive = false;
    Aaron_shoots1(B_alive, C_alive);
    assert(false == B_alive);
    cout << "\tCase 3: Bob alive, Charlie dead\n\t\tAaron is shooting at Bob\n";
    B_alive = true;
    C_alive = false;
    Aaron_shoots1(B_alive, C_alive);
    assert(false == C_alive);
    press_enter();
}
void test_Bob_shoots(void) {
    cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
    bool A_alive = true;
    bool C_alive = true;
    cout << "\tCase 1: Aaron alive, Charlie alive\n\t\tBob is shooting at Charlie\n";
    Bob_shoots(A_alive, C_alive);
    assert(true == A_alive);
    cout << "\tCase 2: Aaron dead, Charlie alive\n\t\tBob is shooting at Charlie\n";
    A_alive = false;
    Bob_shoots(A_alive, C_alive);
    assert(false == A_alive);
    cout << "\tCase 3: Aaron alive, Charlie dead\n\t\tBob is shooting at Aaron\n";
    A_alive = true;
    C_alive = false;
    Bob_shoots(A_alive, C_alive);
    assert(false == C_alive);
    press_enter();
}
void test_Charlie_shoots(void) {
    cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
    bool A_alive = true;
    bool B_alive = true;
    cout << "\tCase 1: Aaron alive, Bob alive\n\t\tCharlie is shooting at Bob\n";
    Charlie_shoots(A_alive, B_alive);
    assert(true == A_alive);
    cout << "\tCase 2: Aaron dead, Bob alive\n\t\tCharlie is shooting at Bob\n";
    A_alive = false;
    Charlie_shoots(A_alive, B_alive);
    assert(false == A_alive);
    cout << "\tCase 3: Aaron alive, Bob dead\n\t\tCharlie is shooting at Aaron\n";
    A_alive = true;
    B_alive = false;
    Charlie_shoots(A_alive, B_alive);
    assert(false == B_alive);
    press_enter();
}
void test_Aaron_shoots2(void) {
    cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
    bool B_alive = true;
    bool C_alive = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n\t\tAaron intentionally misses his first shot\n\t\tBoth Bob and Charlie are alive.\n";
    Aaron_shoots2(B_alive, C_alive);
    assert(true == B_alive);
    cout << "\tCase 2: Bob dead, Charlie alive\n\t\tAaron is shooting at Charlie\n";
    B_alive = false;
    Aaron_shoots2(B_alive, C_alive);
    assert(false == B_alive);
    cout << "\tCase 3: Bob alive, Charlie dead\n\t\tAaron is shooting at Bob\n";
    B_alive = true;
    C_alive = false;
    Aaron_shoots2(B_alive, C_alive);
    assert(false == C_alive);
    press_enter();
}
//Compare strategies
void compare_strategies(int wins1, int wins2) {
    if (wins1 > wins2) {
        cout << "Strategy 1 is better than strategy 2.\n";
    } else if (wins1 < wins2) {
        cout << "Strategy 2 is better than strategy 1.\n";
    } else {
        cout << "The strategies are equally effective.\n";
    }
}
int duel_strategy(int strategy) {
    bool B_alive = true;
    bool A_alive = true;
    bool C_alive = true;
    while (at_least_two_alive(A_alive, B_alive, C_alive)) {
        if (A_alive) {
            if (strategy == 1) {
                Aaron_shoots1(B_alive, C_alive);
            } else if (strategy == 2) {
                Aaron_shoots2(B_alive, C_alive);
            }
        }
        if (B_alive) {
            Bob_shoots(A_alive, C_alive);
        }
        if (C_alive) {
            Charlie_shoots(A_alive, B_alive);
        }
    }
    return A_alive ? 0 : B_alive ? 1 : C_alive ? 2 : -1;
}
//Test for duel_strategy
int test_duel_strategy(int strategy) {
    cout << "Ready to test strategy " << strategy << " (run 10000 times):\n";
    press_enter();
    int A_wins = 0; int B_wins = 0; int C_wins = 0;
    for (int i = 0; i < total_duels; i++) {
        int result = duel_strategy(strategy);
        switch (result) {
            case 0: A_wins++; break;
            case 1: B_wins++; break;
            case 2: C_wins++; break;
            default: break;
        }
    }
    cout << "Aaron won " << A_wins << "/10000 duels or " << (double) A_wins / total_duels * 100 << "%\n";
    cout << "Bob won " << B_wins << "/10000 duels or " << (double) B_wins / total_duels * 100 << "%\n";
    cout << "Charlie won " << C_wins << "/10000 duels or " << (double) C_wins / total_duels * 100 << "%\n";
    cout << endl;
    return A_wins;
}
int main() {
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    srand(time(0));
    rand();
    cout << "*** Welcome to Liam's Duel Simulator ***\n";
    //tests
    test_at_least_two_alive();
    test_Aaron_shoots1();
    test_Bob_shoots();
    test_Charlie_shoots();
    test_Aaron_shoots2();

    //Calls to compare the strategies
    int win_1 = test_duel_strategy(1);
    int win_2 = test_duel_strategy(2);
    compare_strategies(win_1, win_2);
}