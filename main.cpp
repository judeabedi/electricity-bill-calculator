#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const string APPLIANCE_FILE = "appliances.txt";
const string BILL_FILE = "billing_summary.txt";

struct Appliance {
    string name;
    double power;
    double hours;
};

vector<Appliance> applianceList;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string toLowerCase(string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = tolower(text[i]);
    }
    return text;
}

double calculateEnergyPerDay(Appliance item) {
    return (item.power * item.hours) / 1000.0;
}

void saveAppliance(Appliance item) {
    ofstream file(APPLIANCE_FILE, ios::app);

    if (file.is_open()) {
        file << item.name << "," << item.power << "," << item.hours << endl;
        file.close();
    }
}

void loadAppliances() {
    ifstream file(APPLIANCE_FILE);

    if (!file.is_open()) {
        return;
    }

    string name;
    double power;
    double hours;
    char comma;

    while (getline(file, name, ',')) {
        file >> power >> comma >> hours;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        Appliance item;
        item.name = name;
        item.power = power;
        item.hours = hours;

        applianceList.push_back(item);
    }

    file.close();
}

void showMenu() {
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
}

void registerAppliance() {
    Appliance item;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter appliance name: ";
    getline(cin, item.name);

    cout << "Enter power rating (W): ";
    cin >> item.power;

    if (cin.fail()) {
        clearInput();
        cout << "Invalid power input.\n";
        return;
    }

    cout << "Enter usage hours per day: ";
    cin >> item.hours;

    if (cin.fail()) {
        clearInput();
        cout << "Invalid hours input.\n";
        return;
    }

    applianceList.push_back(item);
    saveAppliance(item);

    cout << "Appliance saved successfully.\n";
}

void viewAppliances() {
    if (applianceList.empty()) {
        cout << "No appliances registered.\n";
        return;
    }

    cout << "\nAppliances List\n";

    for (int i = 0; i < applianceList.size(); i++) {
        cout << i + 1 << ". "
             << applianceList[i].name
             << " | Power: " << applianceList[i].power << "W"
             << " | Hours: " << applianceList[i].hours
             << endl;
    }
}

void searchAppliance() {
    if (applianceList.empty()) {
        cout << "No appliances available.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string searchName;
    cout << "Enter appliance name: ";
    getline(cin, searchName);

    searchName = toLowerCase(searchName);

    bool found = false;

    for (int i = 0; i < applianceList.size(); i++) {
        string currentName = toLowerCase(applianceList[i].name);

        if (currentName.find(searchName) != string::npos) {
            cout << applianceList[i].name
                 << " | " << applianceList[i].power << "W"
                 << " | " << applianceList[i].hours << " hrs"
                 << " | " << calculateEnergyPerDay(applianceList[i]) << " kWh/day\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Appliance not found.\n";
    }
}

double getTotalEnergy() {
    double total = 0;

    for (int i = 0; i < applianceList.size(); i++) {
        total += calculateEnergyPerDay(applianceList[i]);
    }

    return total;
}

void energySummary() {
    if (applianceList.empty()) {
        cout << "No appliances.\n";
        return;
    }

    cout << "\nEnergy Summary\n";

    for (int i = 0; i < applianceList.size(); i++) {
        cout << applianceList[i].name
             << " -> "
             << calculateEnergyPerDay(applianceList[i])
             << " kWh/day\n";
    }

    cout << "Total = " << getTotalEnergy() << " kWh/day\n";
}

void calculateBill() {
    if (applianceList.empty()) {
        cout << "No appliances available.\n";
        return;
    }

    double costPerKWh;

    cout << "Enter cost per kWh: ";
    cin >> costPerKWh;

    if (cin.fail()) {
        clearInput();
        cout << "Invalid cost input.\n";
        return;
    }

    double totalEnergy = getTotalEnergy();
    double totalBill = totalEnergy * costPerKWh;

    cout << "\nTotal Energy: " << totalEnergy << " kWh/day\n";
    cout << "Electricity Bill: " << totalBill << endl;

    ofstream file(BILL_FILE);

    if (file.is_open()) {
        file << "Billing Summary\n";
        file << "====================\n";

        for (int i = 0; i < applianceList.size(); i++) {
            file << applianceList[i].name
                 << " -> "
                 << calculateEnergyPerDay(applianceList[i])
                 << " kWh/day\n";
        }

        file << "\nTotal Energy: " << totalEnergy << " kWh/day\n";
        file << "Total Bill: " << totalBill << endl;

        file.close();
    }

    cout << "Billing summary saved to billing_summary.txt\n";
}

int main() {
    loadAppliances();

    int choice;

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            choice = -1;
        }

        if (choice == 1) {
            registerAppliance();
        } else if (choice == 2) {
            viewAppliances();
        } else if (choice == 3) {
            searchAppliance();
        } else if (choice == 4) {
            energySummary();
        } else if (choice == 5) {
            calculateBill();
        } else if (choice == 0) {
            cout << "Goodbye\n";
        } else {
            cout << "Invalid choice\n";
        }

    } while (choice != 0);

    return 0;
}