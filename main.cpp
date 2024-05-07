#include "InventoryManager.h"
#include <iostream>
#include <limits>
#include <regex>

int main() {

    std::string filename = "inventory.csv"; // Filename variable
    InventoryManager manager(filename);

    int choice; // Menu choice variable

    do {
        // Display menu
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Add Vehicle" << std::endl;
        std::cout << "2. Delete Vehicle" << std::endl;
        std::cout << "3. View Inventory" << std::endl;
        std::cout << "4. Save and Exit" << std::endl;
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;

        switch (choice) {

        // Add Vehicle
        case 1: {
            int stockNumber, year;// Variables for Stock Number and Year
            std::string make, model, VIN; // Variables for Make, Model, and VIN

            // Check if Stock Number has been used
            bool uniqueStockNumber = false; // Variable to check if Stock Number is unique
            do {
                // Get Stock Number
                std::cout << "Enter Stock Number: ";
                std::string input;
                std::cin >> input;

                // Validate Stock Number using Regex
                if (std::regex_match(input, std::regex("^\\d+$"))) {
                    stockNumber = std::stoi(input);
                    if (manager.isStockNumberUsed(stockNumber)) {
                        std::cout << "Stock number already exists. Please enter a different one." << std::endl;
                    }
                    else {
                        uniqueStockNumber = true;
                    }
                }
                else {
                    std::cout << "Invalid input. Please enter a valid integer for the stock number." << std::endl;
                }
            } while (!uniqueStockNumber);

            // Get Year
            bool validYear = false; //Variable to check if Year is valid
            do {
                std::cout << "Enter Year: ";
                std::string input;
                std::cin >> input;

                // Validate Year using Regex
                if (std::regex_match(input, std::regex("^\\d{4}$"))) {
                    year = std::stoi(input);
                    if (year >= 1900 && year <= 2030) { // Check if year is within range
                        validYear = true;
                    }
                    else {
                        std::cout << "Year must be between 1900 and 2030. Please try again." << std::endl;
                    }
                }
                else {
                    std::cout << "Invalid input. Year must be exactly 4 digits long. Please try again." << std::endl;
                    std::cin.clear(); // Clear error flags
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                }
            } while (!validYear);

            //Clear newline character from input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


            // Get Make
            std::cout << "Enter Make: ";
            std::getline(std::cin, make);

            // Get Model
            std::cout << "Enter Model: ";
            std::getline(std::cin, model);

            // Get VIN
            bool uniqueVIN = false; // Variable to check if VIN is unique
            do {
                // Get VIN
                std::cout << "Enter VIN: ";
                std::cin >> VIN;

                // Check VIN length
                if (VIN.length() != 17) {
                    std::cout << "VIN must be exactly 17 characters long. Please try again." << std::endl;
                    continue;
                }
                // Check if VIN has been used
                if (manager.isVINUsed(VIN)) {
                    std::cout << "VIN already exists. Please enter a different one." << std::endl;
                }
                else {
                    uniqueVIN = true;
                }
            } while (!uniqueVIN);
                    
            // Add new vehicle to inventory.csv
            InventoryItem* newItem = new InventoryItem(stockNumber, year, make, model, VIN);
            manager.addVehicle(*newItem);
            std::cout << "Vehicle added successfully." << std::endl;
            delete newItem; // Free dynamically allocated memory
            break;
        }

        // Delete Vehicle
        case 2: {
            int stockNumber; // Variable for Stock Number
            std::cout << "Enter Stock Number of vehicle to delete: ";
            std::cin >> stockNumber;
            manager.deleteVehicle(stockNumber);
            break;
        }

        // View Inventory
        case 3:
            manager.viewInventory();
            break;

        // Exit Program
        case 4:
            std::cout << "Exiting program. Goodbye!" << std::endl;
            return 0;

        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear errors and ignore leftover input
            break;
        }
    } while (choice != 4);

    return 0;
}
