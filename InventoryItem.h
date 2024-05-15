// InventoryItem.h
#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <string>

class InventoryItem {
public:
    int stockNumber;
    int year;
    std::string make;
    std::string model;
    int mileage;
    std::string VIN;

    InventoryItem(int sn, int y, const std::string& mk, const std::string& mdl, int m, const std::string& vin);

};

#endif // INVENTORYITEM_H
