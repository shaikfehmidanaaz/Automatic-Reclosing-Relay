#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class AutomaticReclosingRelay {
private:
    bool fault;
    bool breaker;
    int maxAttempts;
    int attempt;

public:
    AutomaticReclosingRelay(int attempts) {
        maxAttempts = attempts;
        attempt = 0;
        fault = false;
        breaker = true;
    }

    void setFault(bool faultStatus) {
        fault = faultStatus;
    }

    void tripBreaker() {
        breaker = false;
        cout << "Circuit Breaker: TRIPPED" << endl;
    }

    void closeBreaker() {
        breaker = true;
        cout << "Circuit Breaker: CLOSED" << endl;
    }

    void startReclosing() {
        cout << "\n===== AUTOMATIC RECLOSING RELAY =====" << endl;

        if (!fault) {
            cout << "Line Status: NORMAL" << endl;
            cout << "Breaker Status: CLOSED" << endl;
            return;
        }

        cout << "Fault Detected!" << endl;

        tripBreaker();

        while (attempt < maxAttempts) {

            attempt++;

            cout << "\nReclosing Attempt " << attempt
                 << " of " << maxAttempts << endl;

            cout << "Waiting before reclosing..." << endl;

            this_thread::sleep_for(chrono::seconds(1));

            closeBreaker();

            if (!fault) {
                cout << "Fault Cleared!" << endl;
                cout << "Line Restored Successfully." << endl;
                return;
            }

            cout << "Fault Still Present!" << endl;

            if (attempt < maxAttempts) {
                tripBreaker();
            }
        }

        cout << "\nMaximum Reclosing Attempts Reached." << endl;
        cout << "Breaker: LOCKED OPEN" << endl;
        cout << "Line remains DISCONNECTED for safety." << endl;

        breaker = false;
    }

    void displayStatus() {
        cout << "\n----- FINAL SYSTEM STATUS -----" << endl;

        if (breaker)
            cout << "Breaker: CLOSED" << endl;
        else
            cout << "Breaker: OPEN" << endl;

        if (fault)
            cout << "Fault: PRESENT" << endl;
        else
            cout << "Fault: CLEARED" << endl;

        cout << "Reclosing Attempts Used: " << attempt << endl;
    }
};

int main() {

    int faultInput;
    int maxAttempts;

    cout << "====================================" << endl;
    cout << "   AUTOMATIC RECLOSING RELAY" << endl;
    cout << "====================================" << endl;

    cout << "\nEnter maximum reclosing attempts: ";
    cin >> maxAttempts;

    cout << "Enter fault status (1 = Fault, 0 = Normal): ";
    cin >> faultInput;

    AutomaticReclosingRelay relay(maxAttempts);

    relay.setFault(faultInput == 1);

    relay.startReclosing();
    relay.displayStatus();

    return 0;
}
