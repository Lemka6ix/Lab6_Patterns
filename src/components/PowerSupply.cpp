#include "PowerSupply.h"

PowerSupply::PowerSupply(const std::string& model, int wattage, double price)
    : model(model), wattage(wattage), price(price) {}

std::string PowerSupply::getModel() const { return model; }
double PowerSupply::getBasePrice() const { return price; }
std::string PowerSupply::getType() const { return "PowerSupply"; }
int PowerSupply::getWattage() const { return wattage; }
bool PowerSupply::isCompatibleWith(const Component&) const { return true; }