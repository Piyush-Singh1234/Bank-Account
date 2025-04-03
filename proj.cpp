#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h> // For Linux sleep functions

using namespace std;

class BankAccount {
private:
    string accountNumber, accountPassword;
    int accountBalance;
public:
    BankAccount() : accountNumber(""), accountPassword(""), accountBalance(0) {}

    void setAccountNumber(string number) {
        accountNumber = number;
    }

    void setAccountPassword(string password) {
        accountPassword = password;
    }

    void setAccountBalance(int balance) {
        accountBalance = balance;
    }

    string getAccountNumber() {
        return accountNumber;
    }

    string getAccountPassword() {
        return accountPassword;
    }

    int getAccountBalance() {
        return accountBalance;
    }
};

void createAccount(BankAccount user) {
    system("clear"); // Clear screen in Linux
    string number, password;

    cout << "\tEnter Account Number: ";
    cin >> number;
    user.setAccountNumber(number);

    cout << "\tEnter a Strong Password: ";
    cin >> password;
    user.setAccountPassword(password);

    user.setAccountBalance(0);

    ofstream outFile("./Account.txt", ios::app); // Relative path
    if (!outFile) {
        cout << "\tError: Unable to Open File!" << endl;
    } else {
        outFile << "\t" << user.getAccountNumber() << " : " << user.getAccountPassword() << " : " << user.getAccountBalance() << endl << endl;
        cout << "\tAccount Created Successfully!" << endl;
    }
    outFile.close();
    usleep(5000000); // Sleep for 5 seconds (Linux)
}

void depositCash() {
    system("clear");
    string number;
    cout << "\tEnter Account Number: ";
    cin >> number;

    ifstream inFile("./Account.txt");
    ofstream outFile("./AccountTemp.txt");
    if (!inFile || !outFile) {
        cout << "\tError: Unable to Open File!" << endl;
        return;
    }

    string line;
    bool accountFound = false;
    while (getline(inFile, line)) {
        stringstream stream(line);
        string storedNumber, storedPassword;
        int storedBalance;
        char delimiter;

        stream >> storedNumber >> delimiter >> storedPassword >> delimiter >> storedBalance;
        if (number == storedNumber) {
            accountFound = true;
            int amount;
            cout << "\tEnter Deposit Amount: ";
            cin >> amount;

            storedBalance += amount;
            outFile << "\t" << storedNumber << " : " << storedPassword << " : " << storedBalance << endl;
            cout << "\tUpdated Balance: " << storedBalance << endl;
        } else {
            outFile << line << endl;
        }
    }
    if (!accountFound) {
        cout << "\tInvalid Account Number!" << endl;
    }
    outFile.close();
    inFile.close();
    remove("./Account.txt");
    rename("./AccountTemp.txt", "./Account.txt");
    usleep(5000000);
}

void withdrawCash() {
    string number, password;
    cout << "\tEnter Account Number: ";
    cin >> number;

    cout << "\tEnter Password: ";
    cin >> password;
    
    ifstream inFile("./Account.txt");
    ofstream outFile("./AccountTemp.txt");
    if (!inFile || !outFile) {
        cout << "\tError: Unable to Open File!" << endl;
        return;
    }

    string line;
    bool accountFound = false;
    while (getline(inFile, line)) {
        stringstream stream(line);
        string storedNumber, storedPassword;
        int storedBalance;
        char delimiter;

        stream >> storedNumber >> delimiter >> storedPassword >> delimiter >> storedBalance;

        if (number == storedNumber && password == storedPassword) {
            accountFound = true;
            int amount;
            cout << "\tEnter Withdrawal Amount: ";
            cin >> amount;
            if (amount <= storedBalance) {
                storedBalance -= amount;
                outFile << "\t" << storedNumber << " : " << storedPassword << " : " << storedBalance << endl;
                cout << "\tTransaction Successful!" << endl;
                cout << "\tRemaining Balance: " << storedBalance << endl;
            } else {
                cout << "\tInsufficient Funds!" << endl;
                outFile << "\t" << storedNumber << " : " << storedPassword << " : " << storedBalance << endl;
            }
        } else {
            outFile << line << endl;
        }
    }
    if (!accountFound) {
        cout << "\tInvalid Account Number or Password!" << endl;
    }
    outFile.close();
    inFile.close();
    remove("./Account.txt");
    rename("./AccountTemp.txt", "./Account.txt");
    usleep(5000000);
}

int main() {
    BankAccount user;

    bool exitProgram = false;
    while (!exitProgram) {
        system("clear");
        int choice;
        cout << "\tBank Account Management System" << endl;
        cout << "\t*********************************" << endl;
        cout << "\t1. Open New Account" << endl;
        cout << "\t2. Deposit Cash" << endl;
        cout << "\t3. Withdraw Cash" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\tEnter Your Choice: ";
        cin >> choice;

        if (choice == 1) {
            createAccount(user);
        } else if (choice == 2) {
            depositCash();
        } else if (choice == 3) {
            withdrawCash();
        } else if (choice == 4) {
            system("clear");
            exitProgram = true;
            cout << "\tGoodbye!" << endl;
            usleep(2000000);
        }
        usleep(3000000);
    }
}
