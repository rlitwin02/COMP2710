//author Ryan Litwin(rpl0010@auburn.edu)
// Project 1, project1_Litwin_rpl0010.cpp
//version 9/1/2020
// compile using  g++ project1_Litwin_rpl0010.cpp -o a.out
// run ./a.out

#include <iostream>
using namespace std;

int main(){ //variables
    float loan = -1;
    float interest = -1;
    float monthlyPayments = -1;
    int currentMonth = 0;
    float totalInterest = 0;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    while (loan <= 0) {
        cout << "\nLoan Amount: ";
        cin >> loan;
    }

    while (interest <= -1) {
        cout << "Interest Rate (% per year): ";
        cin >> interest;
    }
    // finding the interestRate from interest
    float interestRate = interest / 12 / 100;

    while (monthlyPayments <= 0 || monthlyPayments <= loan * interestRate) {
        cout << "Monthly Payments: ";
        cin >> monthlyPayments;
    }
    
    
    cout << endl;
    // amortization table
    cout << "*****************************************************************\n"
	     << "\tAmortization Table\n"
	     << "*****************************************************************\n"
	     << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";
    
    
    while (loan > 0) {
        if (currentMonth == 0) {
            cout << currentMonth++ << "\t$" << loan;
            if (loan < 1000) cout << "\t";
                cout << "\t" << "N/A\tN/A\tN/A\t\tN/A\n";
        }
        else {
            float interestPayment = loan * interestRate;
            float principal = monthlyPayments - interestPayment;
            loan -= principal;
            totalInterest += interestPayment;

            if (loan < 0) {
                    principal += loan;
                    monthlyPayments += loan;
                    loan = 0;
            }
            
            

            cout << currentMonth++ << "\t$" << loan;
            if (loan < 1000) cout << "\t";
            cout << "    \t$" << monthlyPayments << "\t" << interestRate * 100 << "\t$" << interestPayment << "\t\t$" << principal << "\n";

        }
        
    }

    cout << "****************************************************************\n";
    cout << "\nIt takes " << --currentMonth << " months to pay off "
         << "the loan.\n"
         << "Total interest paid is: $" << totalInterest;
    cout << endl << endl;
    return 0;


}