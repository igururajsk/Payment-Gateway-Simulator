#include <iostream>
#include <string>
#include <memory>
#include <random>
using namespace std;
class Transaction {
private:
    string transactionID;
    double amount;
    string status;
    string timestamp;

public:
    Transaction(string id, double amt, string st) : transactionID(id), amount(amt), status(st) {
        // Generate timestamp
        time_t now = time(0);
        timestamp = ctime(&now);
        timestamp.pop_back(); // remove newline character
    }

    string getID() const { return transactionID; }
    double getAmount() const { return amount; }
    string getStatus() const { return status; }
    string getTimestamp() const { return timestamp; }

    string toString() const {
        return transactionID + " | $" + to_string(amount) + " | " + status + " | " + timestamp;
    }
};
class PaymentGateway {
private:
    vector<Transaction> transactions;
    int transactionCounter;

    string generateID() {
        transactionCounter++;
        return "TXN" + to_string(1000 + transactionCounter);
    }
    bool validateAmount(double amount) {
        if (amount <= 0) {
            cout << "Error: Amount must be greater than 0." << endl;
            return false;
        }
        return true;
    }
public:
    PaymentGateway() : transactionCounter(0) {}

    void processPayment(double amount) {
        if (!validateAmount(amount)) return;

        string id = generateID();
        string status = "SUCCESS";

        // Simulating  random failure
        if (rand() % 10 == 0) { // 10% chance to fail
            status = "FAILED";
        }

        Transaction t(id, amount, status);
        transactions.push_back(t);

        // Saving  to file
        ofstream file("transactions.txt", ios::app);
        if (file.is_open()) {
            file << t.toString() << endl;
            file.close();
        } else {
            cout << "Error: Could not write to file!" << endl;
        }

        cout << "Transaction " << status << "! ID: " << id << endl;
    }

    void showAllTransactions() {
        cout << "\n--- Transaction Records ---\n";
        for (const auto& t : transactions) {
            cout << t.toString() << endl;
        }
        cout << "---------------------------\n";
    }
};
int main() {
    srand(time(0)); //Random Generator 
    PaymentGateway gateway;

    int choice;
    do {
        cout << "\n1. Make Payment\n2. Show Transactions\n3. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            double amount;
            cout << "Enter payment amount: $";
            cin >> amount;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Try again." << endl;
                continue;
            }

            gateway.processPayment(amount);
        } else if (choice == 2) {
            gateway.showAllTransactions();
        } else if (choice == 3) {
            cout << "Exiting..." << endl;
        } else {
            cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 3);

    return 0;
}

