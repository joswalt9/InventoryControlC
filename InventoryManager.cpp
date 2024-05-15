// InventoryManager.cpp
#include "InventoryManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

InventoryManager::InventoryManager(const std::string& fname) : filename(fname) {
    readInventory();
}

InventoryManager::~InventoryManager() {
    saveInventory();
}

//Read Inventory
void InventoryManager::readInventory() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    bool header = true;
    while (std::getline(file, line)) {
        if (header) {
            header = false;
            continue;
        }
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() == 6) {
            InventoryItem item(std::stoi(tokens[0]), std::stoi(tokens[1]), tokens[2], tokens[3], std::stoi(tokens[4]), tokens[5]);
            inventory.push_back(item);
        }
    }
    file.close();
}

//Save Inventory
void InventoryManager::saveInventory() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file << "StockNumber,Year,Make,Model,Mileage, VIN" << std::endl;
    for (const auto& item : inventory) {
        file << item.stockNumber << "," << item.year << "," << item.make << "," << item.model << "," << item.mileage << "," << item.VIN << std::endl;
    }
    file.close();
}

void InventoryManager::addVehicle(const InventoryItem& item) {
    inventory.push_back(item);
}

//Delete Vehicle
void InventoryManager::deleteVehicle(int stockNumber) {
    auto it = std::find_if(inventory.begin(), inventory.end(), [stockNumber](const InventoryItem& item) {
        return item.stockNumber == stockNumber;
        });

    if (it != inventory.end()) {
        inventory.erase(it);
        std::cout << "Vehicle successfully deleted" << std::endl;
    }
    else {
        std::cerr << "Vehicle with stock number " << stockNumber << " not found." << std::endl;
    }
}

//View Inventory
void InventoryManager::viewInventory() {
    std::sort(inventory.begin(), inventory.end(), [](const InventoryItem& a, const InventoryItem& b) {
        return a.stockNumber < b.stockNumber;
        });
    std::cout << "Stock #  Year    Make      Model     Mileage     VIN" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    for (const auto& item : inventory) {
        std::cout << std::setw(9) << std::left << item.stockNumber;
        std::cout << std::setw(8) << std::left << item.year;
        std::cout << std::setw(10) << std::left << item.make;
        std::cout << std::setw(10) << std::left << item.model;
        std::cout << std::setw(9) << std::left << item.mileage;
        std::cout << std::setw(13) << std::left << item.VIN;
        std::cout << std::endl;
    }
}

//Check if Stock Number has been previously used
bool InventoryManager::isStockNumberUsed(int stockNumber) const {
    auto it = std::find_if(inventory.begin(), inventory.end(), [stockNumber](const InventoryItem& item) {
        return item.stockNumber == stockNumber;
        });

    return it != inventory.end();
}

//Check if VIN has been previously used
bool InventoryManager::isVINUsed(const std::string& VIN) const {
    auto it = std::find_if(inventory.begin(), inventory.end(), [VIN](const InventoryItem& item) {
        return item.VIN == VIN;
        });

    return it != inventory.end();
}
