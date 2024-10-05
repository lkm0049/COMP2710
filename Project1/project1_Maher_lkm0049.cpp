//Name: Liam Maher
//UserID: lkm0049
//filename: project1_Maher_lkm0049.cpp
//Project: COMP 2710 Project 1
//Date: 9/20/2019
//Compile: g++ project1_Maher_lkm0049.cpp -o Project1.out
//Run: ./Project1.out

#include <iostream>
#include <iomanip>
using namespace std;
 
int main() {

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    //Variables to be used in program
    float loanAmount = -1;
    float interestRate = -1;
    float monthlyPayment = -1;

    //Function for user input of loanAmount

    while (loanAmount < 0) {
        cout << "Loan Amount: ";
        cin >> loanAmount;
    }
    //Function for user input of interestRate
    while (interestRate < 0) {
        cout << "Interest Rate (% per year): ";
        cin >> interestRate;
    }

    //Function for user input of monthlyPayment
    float monthlyInterestRate = interestRate / 12 / 100;

    while (monthlyPayment <= 0 || monthlyPayment < (loanAmount * monthlyInterestRate)) {
        cout << "Monthly Payments: ";
        cin >> monthlyPayment;
    }

    cout << endl;

    //Code for the Amoritaztion Table
    cout << "**********************************************************\n"
         << "\tAmortization Table\n"
         << "**********************************************************\n"
         << "Month   Balance   Payment      Rate   Interest   Principal\n";  

    //Calculations for the Amoritaztion Table

    int currentMonth = 0;
    float interestTotal = 0;

    while (loanAmount > 0) {
        if (currentMonth == 0) {
            cout << currentMonth++ << "\t$" << loanAmount;
            if (loanAmount < 1000) cout << "\t";
            cout << "  N/A\t       N/A    N/A        N/A\n";
        }
        
        else {
            float interestPayment = loanAmount * monthlyInterestRate;
            float principalPayment = monthlyPayment - interestPayment;
            loanAmount -= principalPayment;
            interestTotal += interestPayment;

            if (loanAmount < 0) {
                monthlyPayment += loanAmount;
                principalPayment += loanAmount;
                loanAmount = 0;
            }

            cout << currentMonth++ << "\t$" << loanAmount;
            if (loanAmount < 1000) cout << "\t";
            cout << "  $" << monthlyPayment << "       " << monthlyInterestRate * 100 << "   $" << interestPayment << "\t $" << principalPayment << "\n";   
        }
    }
    cout << "**********************************************************\n";
    cout << "\nIt takes " << --currentMonth << " months to pay off the loan.\n";
    cout     << "Total interest paid is: $" << interestTotal;
    cout << endl << endl;

    return 0;
}