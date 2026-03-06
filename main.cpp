#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Appliance {
    string name;
    double powerW;
    double hoursPerDay;

    double energyKWhPerDay() const {
        return (powerW * hoursPerDay) / 1000.0;
    }
};

vector<Appliance> appliances;

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

Appliance registerAppliance() {
    Appliance a;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter appliance name: ";
    getline(cin, a.name);

    cout << "Enter power rating (W): ";
    cin >> a.powerW;

    cout << "Enter usage hours per day: ";
    cin >> a.hoursPerDay;

    cout << "Appliance registered successfully.\n";
    return a;
}

int main() {
    while (true) {
        int choice = menu();

        switch (choice) {
            case 1:
                appliances.push_back(registerAppliance());
                break;

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