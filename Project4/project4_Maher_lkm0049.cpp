//Name: Liam Maher
//Date: 4/20/2020
//User: lkm0049
//Filename: project4_Maher_lkm0049.cpp
//Compile: g++ project4_Maher_lkm0049.cpp -o Project4.out
//Compile for testing: g++ -DUNIT_TESTING project4_Maher_lkm0049.cpp -o Project4.out
//Run: ./Project4.out

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

int numberQuestions = 0;

struct TriviaNode {
    string question;
    string answer;
    int points;
    TriviaNode* next;
};
typedef TriviaNode* TriviaNodePtr;

void initialize_question_list(TriviaNodePtr& question_list);
void add_question(TriviaNodePtr& question_list);
int ask_question(TriviaNodePtr question_list, int num_asked);
void Unit_Test();



#define Triv_Quiz
//#define UNIT_TESTING commented out to see if this will get rid of macro error
int main() {

#ifndef UNIT_TESTING
#ifdef Triv_Quiz
    TriviaNodePtr node_list = new TriviaNode;
    initialize_question_list(node_list);
    cout << "*** Welcome to Liam's trivia quiz game ***" << endl;
    string input;
    do {
        add_question(node_list);
        cout << "Continue? (Yes/No): ";
        getline(cin, input);
    } while (input.compare("Yes")==0 || input.compare("yes")==0);
    cout << endl;

    ask_question(node_list, numberQuestions);
    cout << "*** Thank you for playing the trivia quiz game.  Goodbye! ***" << endl;
    return 0;
#endif
#endif

#ifdef UNIT_TESTING
	Unit_Test();
	return 0;
#endif
}


void initialize_question_list(TriviaNodePtr& question_list) {

    TriviaNodePtr current_point = new TriviaNode;


    //Q1
    current_point->question = "How long was the shortest war on record? (Hint: how many minutes)";
    current_point->answer = "38";
    current_point->points = 100;
    current_point->next = new TriviaNode;
    
    question_list = current_point;
    current_point = current_point->next;

    //Q2
    current_point->question = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
    current_point->answer = "Bank of Italy";
    current_point->points = 50;
    current_point->next = new TriviaNode;
    current_point = current_point->next;

    //Q3
    current_point->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
    current_point->answer = "Wii Sports";
    current_point->points = 20;
    current_point->next = NULL;
    numberQuestions += 3;
}

void add_question(TriviaNodePtr& question_list) {
    TriviaNodePtr new_point = new TriviaNode;

    cout << "Enter a question: ";
    getline(cin, new_point->question);
    cout << "Enter an answer: ";
    getline(cin, new_point->answer);
    cout << "Enter award points: ";
    cin >> new_point->points;
    cin.ignore();
    new_point->next = NULL;

    TriviaNode* last = question_list;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_point;
    numberQuestions++;
}


int ask_question(TriviaNodePtr question_list, int num_asked) {
    TriviaNodePtr current_point = question_list;
    string user_input;
    int total_points = 0;

    if (question_list == NULL || num_asked == 0) {
        cout << "Warning - The number of trivia to be asked must equal to or be larger than 1." << endl;
        return 1;
    } else if (numberQuestions < num_asked) {
        cout << "Warning - there is only " << numberQuestions << " trivia in the list." << endl;
        return 1;
    } else {
        for (int i = 0; i < num_asked; i++) {
            cout << "Question: " << current_point->question << endl;
            cout << "Answer: ";
            getline(cin, user_input);
            if (user_input.compare(current_point->answer) == 0) {
                cout << "Your answer is correct. You receive " << current_point->points << " points." << endl;
                total_points += current_point->points;
            } else {
                cout << "Your answer is wrong. The correct answer is: " << current_point->answer << endl;
            }
            cout << "Your total points: " << total_points << endl << endl;
            current_point = current_point->next;
        }
    }
    return 0;
}

void Unit_Test() {
	cout << "*** This is a debugging version ***\n";

	TriviaNodePtr node_list = new TriviaNode;
	initialize_question_list(node_list);

	cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
	assert(ask_question(node_list, 0) == 1) ; //Assert return value 1
	cout << "Case 1 passed\n\n";

	cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
	assert(ask_question(node_list,1) == 0); //Assert return value 0
	cout << "Case 2.1 passed\n\n";

	cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
	assert(ask_question(node_list,1) == 0); //Assert return value 0
	cout << "Case 2.2 passed\n\n";

	cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list." << endl;
	assert(ask_question(node_list, 3) == 0); //Assert return value 0
	cout << "Case 3 passed\n\n";

	cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
	assert(ask_question(node_list,5) == 1); //Assert return value 1
	cout << "Case 4 passed\n\n";

	cout << "*** End of the Debugging Version ***" << endl;
}