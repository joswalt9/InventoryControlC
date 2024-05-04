#include "InventoryManager.h"
#include <iostream>
#include <limits>

int main() {
    std::string filename = "inventory.csv";
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
            int stockNumber, year;
            std::string make, model, VIN;

            // Check if Stock Number has been used
            bool uniqueStockNumber = false;
            do {
                // Get Stock Number
                std::cout << "Enter Stock Number: ";
                std::cin >> stockNumber;
                // Check if Stock Number has been used
                if (manager.isStockNumberUsed(stockNumber)) {
                    std::cout << "Stock number already exists. Please enter a different one." << std::endl;
                }
                else {
                    uniqueStockNumber = true;
                }
            } while (!uniqueStockNumber);

            // Get Year
            do {
                std::cout << "Enter Year: ";
                std::cin >> year;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input

                //Check Year Length
                if (std::to_string(year).length() != 4) {
                    std::cout << "Year must be exactly 4 characters long. Please try again." << std::endl;
                }
            } while (std::to_string(year).length() != 4);


            // Get Make
            std::cout << "Enter Make: ";
            std::getline(std::cin, make);

            // Get Model
            std::cout << "Enter Model: ";
            std::getline(std::cin, model);

            // Get VIN
            bool uniqueVIN = false;
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

            //Add new vehicle to inventory.csv
            InventoryItem* newItem = new InventoryItem(stockNumber, year, make, model, VIN);
            manager.addVehicle(*newItem);
            std::cout << "Vehicle added successfully." << std::endl;
            delete newItem; // Free dynamically allocated memory
            break;
        }

        //Delete Vehicle
        case 2: {
            int stockNumber;
            std::cout << "Enter Stock Number of vehicle to delete: ";
            std::cin >> stockNumber;
            manager.deleteVehicle(stockNumber);
            break;
        }
        case 3:
            manager.viewInventory();
            break;
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
