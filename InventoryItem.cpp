// InventoryItem.cpp
#include "InventoryItem.h"

InventoryItem::InventoryItem(int sn, int y, const std::string& mk, const std::string& mdl, const std::string& vin)
    : stockNumber(sn), year(y), make(mk), model(mdl), VIN(vin) {}
