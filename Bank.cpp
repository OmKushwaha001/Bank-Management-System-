#include<iostream>
#include<string>
#include<conio.h>  
using namespace std;

int getPIN() {
    int pin = 0;
    char ch;
    while ((ch = getch()) != 13) { 
        if (ch >= '0' && ch <= '9') {
            cout << "*";
            pin = pin * 10 + (ch - '0');
        }
    }
    cout << endl;
    return pin;
}

class Bank {
protected:
    double balance;
    string lastTransaction;

public:
    Bank() {
        balance = 0.0;
        lastTransaction = "No transactions yet";
    }

    virtual void Deposit(double amt) {
        balance += amt;
        lastTransaction = "Deposited: " + to_string(amt);
        cout << "\nAmount Deposited Successfully!" << endl;
    }

    virtual void Withdraw(double amt) {
        if(balance >= amt) {
            balance -= amt;
            lastTransaction = "Withdrawn: " + to_string(amt);
            cout << "\nWithdrawal Successful!" << endl;
        } else {
            cout << "\nInsufficient Balance!" << endl;
        }
    }

    double getBalance() {
        return balance;
    }

    void showLastTransaction() {
        cout << "Last Transaction: " << lastTransaction << endl;
    }

    virtual void accountType() {
        cout << "Generic Bank Account" << endl;
    }
};

class SavingsAccount: public Bank {
public:
    void Deposit(double amt) override {
        double bonus = 0.02 * amt;  // 2% bonus reward
        balance += (amt + bonus);
        lastTransaction = "Savings Deposit: " + to_string(amt) + " + Bonus " + to_string(bonus);
        cout << "\nSavings Account Deposit Successful with Bonus!" << endl;
    }

    void Withdraw(double amt) override {
        if(balance >= amt) {
            balance -= amt;
            lastTransaction = "Savings Withdraw: " + to_string(amt);
            cout << "\nSavings Withdrawal Done!" << endl;
        } else {
            cout << "\nNot Enough Money in Savings!" << endl;
        }
    }

    void accountType() override {
        cout << "Savings Account (Includes 2% bonus on deposit)" << endl;
    }
};

class CurrentAccount: public Bank {
public:
    void accountType() override {
        cout << "Current Account (No bonus, unlimited transactions)" << endl;
    }
};

int main() {
    Bank* cust;
    int type;
    int choice;
    double amt;
    int pin, enteredPin;

    cout << "Choose Account Type:\n1. Savings\n2. Current\nEnter: ";
    cin >> type;

    if(type == 1) cust = new SavingsAccount();
    else cust = new CurrentAccount();
    
    cout << "\nSet your ATM PIN: ";
    pin = getPIN();

    cout << "\nWelcome to the Banking System\n";

    cout << "Enter PIN to continue: ";
    enteredPin = getPIN();
    if(enteredPin != pin) {
        cout << "Incorrect PIN! Intruder Alert!" << endl;
        return 0;
    }

    cust->accountType();

    while(true) {
        cout << "\n===== ATM MENU =====\n";
        cout << "1. Deposit\n2. Withdraw\n3. Check Balance\n4. Last Transaction\n5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Deposit Amount: ";
                cin >> amt;
                cust->Deposit(amt);
                break;

            case 2:
                cout << "Enter Withdrawal Amount: ";
                cin >> amt;
                cust->Withdraw(amt);
                break;

            case 3:
                cout << "Current Balance: Rs. " << cust->getBalance() << endl;
                break;

            case 4:
                cust->showLastTransaction();
                break;

            case 5:
                cout << "\nThanks for using our ATM\n";
                delete cust;
                return 0;

            default:
                cout << "Invalid Input, Try Again!" << endl;
        }
    }
}
     
