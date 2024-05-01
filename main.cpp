#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <direct.h>
#include <iomanip>
#include <algorithm>
#include <cctype>


using namespace std;

string filename; // Global variable to store the path to the inventory file

//Define structure for InventoryItem
struct InventoryItem {
    int stockNumber;
    int year;
    string make;
    string model;
    string VIN;
};

//Sort by Stock Number in viewInventory Function
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

    // Gather information about the new vehicle from the user
    InventoryItem newItem;

    // Get Stock Number
    bool validStockNumber = false;
    while (!validStockNumber) {
        cout << "Enter Stock Number: ";
        string input;
        cin >> input;
        bool validInput = true;
        for (char c : input) {
            if (!isdigit(c)) {
                validInput = false;
                break;
            }
        }
        if (validInput) {
            newItem.stockNumber = stoi(input);
            validStockNumber = true;
        }
        else {
            cout << "Invalid input. Please enter a valid integer for the stock number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Get Year
    bool validYear = false;
    while (!validYear) {
        cout << "Enter Year: ";
        string input;
        cin >> input;
        bool validInput = true;
        for (char c : input) {
            if (!isdigit(c)) {
                validInput = false;
                break;
            }
        }
        if (validInput) {
            newItem.year = stoi(input);
            validYear = true;
        }
        else {
            cout << "Invalid input. Please enter a valid integer for the year." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    //Get Make
    cout << "Enter Make: ";
    cin >> newItem.make;

    //Get Model
    cout << "Enter Model: ";
    cin >> newItem.model;

    //Get VIN
    do {
        cout << "Enter VIN (must be exactly 16 characters): "; //Check VIN validation
        cin >> newItem.VIN;
        if (newItem.VIN.length() != 16) {
            cout << "Invalid VIN length. Please enter exactly 16 characters." << endl;
        }
    } while (newItem.VIN.length() != 16);

    // Open the CSV file for appending
    ofstream file(filename, ios_base::app); // Open for appending

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    // Append the new vehicle information to the CSV file
    file << newItem.stockNumber << "," << newItem.year << "," << newItem.make << "," << newItem.model << "," << newItem.VIN << endl;

    file.close();

    cout << "Vehicle added successfully." << endl;
}

//Delete Vehicle Function
void deleteVehicle() {
    cout << "Deleting Vehicle..." << endl;
    // Implement deleting vehicle functionality here
}

//View Inventory Function
void viewInventory() {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
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
                    item.year = stoi(token);
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
    cout << "Stock #  Year    Make    Model     VIN" << endl;
    cout << "-----------------------------------------" << endl;

    for (const auto& item : inventory) {
        cout << setw(9) << left << item.stockNumber;
        cout << setw(8) << left << item.year;
        cout << setw(8) << left << item.make;
        cout << setw(10) << left << item.model;
        cout << setw(13) << left << item.VIN;
        cout << endl;
    }
}

//Main Program
int main() {

    // Get the current working directory and construct the file path
    char buffer[FILENAME_MAX];
    if (!_getcwd(buffer, FILENAME_MAX)) {
        cerr << "Error getting current working directory." << endl;
        return 1;
    }
    filename = string(buffer) + "\\inventory.csv";

    int choice; //Menu choice variable

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
