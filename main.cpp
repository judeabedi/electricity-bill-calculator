#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>
#include <fstream>

using namespace std;

const string APPLIANCE_FILE = "appliances.txt";

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

string toLowerStr(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c){ return tolower(c); });
    return s;
}

void saveApplianceToFile(const Appliance& a) {
    ofstream file(APPLIANCE_FILE, ios::app);
    if (file.is_open()) {
        file << a.name << "," << a.powerW << "," << a.hoursPerDay << endl;
        file.close();
    }
}

void loadAppliancesFromFile() {
    ifstream file(APPLIANCE_FILE);
    if (!file.is_open()) return;

    Appliance a;
    while (getline(file, a.name, ',')) {
        file >> a.powerW;
        file.ignore();
        file >> a.hoursPerDay;
        file.ignore();
        appliances.push_back(a);
    }
    file.close();
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

    saveApplianceToFile(a);
    cout << "Appliance saved successfully.\n";
    return a;
}

void viewAppliances() {
    if (appliances.empty()) {
        cout << "No appliances registered.\n";
        return;
    }

    cout << "\nAppliances List\n";
    for (size_t i = 0; i < appliances.size(); i++) {
        cout << i + 1 << ". "
             << appliances[i].name
             << " | Power: " << appliances[i].powerW
             << "W | Hours: " << appliances[i].hoursPerDay
             << endl;
    }
}

double totalEnergy() {
    double total = 0;
    for (auto &a : appliances) total += a.energyKWhPerDay();
    return total;
}

void energySummary() {
    if (appliances.empty()) {
        cout << "No appliances.\n";
        return;
    }

    cout << "\nEnergy Summary\n";
    for (auto &a : appliances) {
        cout << a.name << " -> " << a.energyKWhPerDay() << " kWh/day\n";
    }
    cout << "Total = " << totalEnergy() << " kWh/day\n";
}

void searchAppliance() {
    if (appliances.empty()) {
        cout << "No appliances available.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string name;
    cout << "Enter appliance name: ";
    getline(cin, name);

    string q = toLowerStr(name);
    bool found = false;

    for (auto &a : appliances) {
        if (toLowerStr(a.name).find(q) != string::npos) {
            cout << a.name
                 << " | " << a.powerW << "W"
                 << " | " << a.hoursPerDay << " hrs"
                 << " | " << a.energyKWhPerDay() << " kWh/day\n";
            found = true;
        }
    }

    if (!found) cout << "Appliance not found.\n";
}

void calculateBill() {
    if (appliances.empty()) {
        cout << "No appliances available.\n";
        return;
    }

    double cost;
    cout << "Enter cost per kWh: ";
    cin >> cost;

    if (cin.fail()) {
        clearBadInput();
        cout << "Invalid cost.\n";
        return;
    }

    double energy = totalEnergy();
    double bill = energy * cost;

    cout << "\nTotal Energy: " << energy << " kWh/day\n";
    cout << "Electricity Bill: " << bill << endl;
}

int main() {
    loadAppliancesFromFile();

    while (true) {
        int choice = menu();

        switch (choice) {
            case 1:
                appliances.push_back(registerAppliance());
                break;
            case 2:
                viewAppliances();
                break;
            case 3:
                searchAppliance();
                break;
            case 4:
                energySummary();
                break;
            case 5:
                calculateBill();
                break;
            case 0:
                cout << "Goodbye\n";
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
}