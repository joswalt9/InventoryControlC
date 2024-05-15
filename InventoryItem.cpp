// InventoryItem.cpp
#include "InventoryItem.h"

InventoryItem::InventoryItem(int sn, int y, const std::string& mk, const std::string& mdl, int m, const std::string& vin)
    : stockNumber(sn), year(y), make(mk), model(mdl), mileage(m), VIN(vin) {}
