#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <direct.h>
#include <iomanip>
#include <algorithm>

using namespace std;

//Define structure for InventoryItem

struct InventoryItem {
    int stockNumber;
    string year;
    string make;
    string model;
    string VIN;
};

//Sort by Stock Number

bool compareStockNumber(const InventoryItem& a, const InventoryItem& b) {
    return a.stockNumber < b.stockNumber;
}

// Function prototypes
void addVehicle();
void deleteVehicle();
void viewInventory();
void saveInventory();


//Add Vehicle Function
void addVehicle() {
    cout << "Adding Vehicle..." << endl;
    // Implement adding vehicle functionality here
}

//Delete Vehicle Function
void deleteVehicle() {
    cout << "Deleting Vehicle..." << endl;
    // Implement deleting vehicle functionality here
}
//View Inventory Function
void viewInventory() {
    char buffer[FILENAME_MAX];  // Create a buffer to hold the path
    if (!_getcwd(buffer, FILENAME_MAX)) {
        cerr << "Error getting current working directory." << endl;
        return;
    }

    string filePath = string(buffer) + "\\inventory.csv";  // Construct the full path

    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return;
    }

    string line;
    bool header = true;  // Flag to indicate if it's the header line
    vector <InventoryItem> inventory;

    while (getline(file, line)) {
        if (header) {
            header = false;  // Skip the header line
        }
        else {
            vector<string> tokens;
            stringstream ss(line);
            string token;

            InventoryItem item;

            int index = 0; // Index to keep track of the field position
            while (getline(ss, token, ',')) {
                switch (index) {
                case 0:
                    item.stockNumber = stoi(token);
                    break;
                case 1:
                    item.year = token;
                    break;
                case 2:
                    item.make = token;
                    break;
                case 3:
                    item.model = token;
                    break;
                case 4:
                    item.VIN = token;
                    break;
                }
                index++;
            }

            inventory.push_back(item);
        }
    }

    file.close();

    // Sort the inventory by stock number
    sort(inventory.begin(), inventory.end(), compareStockNumber);

    // Display the sorted inventory
    cout << "Stock #      Year   Make    Model   VIN" << endl;
    cout << "-----------------------------------------" << endl;

    for (const auto& item : inventory) {
        cout << setw(13) << left << item.stockNumber;
        cout << setw(8) << left << item.year;
        cout << setw(8) << left << item.make;
        cout << setw(8) << left << item.model;
        cout << setw(13) << left << item.VIN;
        cout << endl;
    }
}
void saveInventory() {
    cout << "Saving Inventory..." << endl;
    // Implement saving the inventory here
    // Placeholder for saving the inventory
}
//Main Program
int main() {
    int choice;

    do {
        // Display menu
        cout << "Menu:" << endl;
        cout << "1. Add Vehicle" << endl;
        cout << "2. Delete Vehicle" << endl;
        cout << "3. View Inventory" << endl;
        cout << "4. Save and Exit" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
        case 1:
            addVehicle();
            break;
        case 2:
            deleteVehicle();
            break;
        case 3:
            viewInventory();
            break;
        case 4:
            saveInventory();
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4);

    return 0;
}
