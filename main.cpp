#include <iostream>
#include <limits>
using namespace std;

void clearBadInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int menu() {
    cout << "\n==============================\n";
    cout << " Electrical Load Monitoring\n";
    cout << "==============================\n";
    cout << "1. Register appliance\n";
    cout << "2. View appliances\n";
    cout << "3. Search appliance\n";
    cout << "4. Energy summary\n";
    cout << "5. Calculate electricity bill\n";
    cout << "0. Exit\n";
    cout << "Choose: ";

    int choice;
    cin >> choice;

    if (cin.fail()) {
        clearBadInput();
        return -1;
    }
    return choice;
}

int main() {
    while (true) {
        int choice = menu();

        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                cout << "Feature not implemented yet.\n";
                break;

            case 0:
                cout << "Goodbye\n";
                return 0;

            default:
                cout << "Invalid choice\n";
        }
    }
}