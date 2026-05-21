#include "Storage.h"

Storage::Storage(const std::string& model, const std::string& interface, int capacity, double price)
    : model(model), interface(interface), capacity(capacity), price(price) {}

std::string Storage::getModel() const { return model; }
double Storage::getBasePrice() const { return price; }
std::string Storage::getType() const { return "Storage"; }
bool Storage::isCompatibleWith(const Component&) const { return true; }