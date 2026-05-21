#include "Cooling.h"

Cooling::Cooling(const std::string& model, const std::string& type, int tdp, double price)
    : model(model), type(type), tdp(tdp), price(price) {}

std::string Cooling::getModel() const { return model; }
double Cooling::getBasePrice() const { return price; }
std::string Cooling::getType() const { return "Cooling"; }
bool Cooling::isCompatibleWith(const Component&) const { return true; }