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


