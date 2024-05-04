// InventoryManager.h
#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include "InventoryItem.h"
#include <vector>
#include <string>

class InventoryManager {
private:
    std::vector<InventoryItem> inventory;
    std::string filename;

    void readInventory();
    void saveInventory();

public:
    InventoryManager(const std::string& fname);
    ~InventoryManager();

    void addVehicle(const InventoryItem& item);
    void deleteVehicle(int stockNumber);
    void viewInventory();
    bool isStockNumberUsed(int stockNumber) const;
    bool isVINUsed(const std::string& VIN) const;
};

#endif // INVENTORYMANAGER_H
