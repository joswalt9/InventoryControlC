//main.cpp

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
            int stockNumber, year, mileage;// Variables for Stock Number, Mileage, and Year
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
            bool validYear = false; // Variable to check if Year is valid
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

            // Clear newline character from input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


            // Get Make
            bool validMake = false; // Variable to check if Make is valid
            do {
                std::cout << "Enter Make (up to 15 characters): ";
                std::getline(std::cin, make);

                // Validate Make length
                if (make.length() <= 15 && !make.empty()) {
                    validMake = true;
                }
                else {
                    std::cout << "Make must be non-empty and contain up to 15 characters. Please try again." << std::endl;
                }
            } while (!validMake);

            // Get Model
            bool validModel = false; // Variable to check if Model is valid
            do {
                std::cout << "Enter Model (up to 15 characters): ";
                std::getline(std::cin, model);

                // Validate Model length
                if (model.length() <= 15 && !model.empty()) {
                    validModel = true;
                }
                else {
                    std::cout << "Model must be non-empty and contain up to 15 characters. Please try again." << std::endl;
                }
            } while (!validModel);

            // Get Mileage
            bool validMileage = false; // Variable to check if Mileage is valid
            do {
                std::cout << "Enter Mileage: ";
                std::string input;
                std::cin >> input;

                // Validate Mileage using Regex
                if (std::regex_match(input, std::regex("^\\d{1,6}$"))) {
                    mileage = std::stoi(input);
                    validMileage = true;
                }
                else {
                    std::cout << "Invalid input. Mileage must be an integer up to 6 characters long. Please try again." << std::endl;
                    std::cin.clear(); // Clear error flags
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                }
            } while (!validMileage);

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
            InventoryItem* newItem = new InventoryItem(stockNumber, year, make, model, mileage, VIN);
            manager.addVehicle(*newItem);
            std::cout << "Vehicle added successfully." << std::endl;
            delete newItem; // Free dynamically allocated memory
            break;
        }

        // Delete Vehicle
case 2: {
    int stockNumber; // Variable for Stock Number
    bool validStockNumber = false; // Variable to check if Stock Number is valid

    do {
        std::cout << "Enter Stock Number of vehicle to delete: ";
        std::string input;
        std::cin >> input;

        // Validate input as integer
        if (std::regex_match(input, std::regex("^\\d+$"))) {
            stockNumber = std::stoi(input);
            validStockNumber = true;
        }
        else {
            std::cout << "Invalid input. Please enter a valid integer for the stock number." << std::endl;
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    } while (!validStockNumber);

    // Check if the vehicle exists before attempting deletion
    if (manager.isStockNumberUsed(stockNumber)) {
        manager.deleteVehicle(stockNumber);
        std::cout << "Vehicle with Stock Number " << stockNumber << " deleted successfully." << std::endl;
    }
    else {
        std::cout << "Vehicle with Stock Number " << stockNumber << " does not exist in the inventory." << std::endl;
    }
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
