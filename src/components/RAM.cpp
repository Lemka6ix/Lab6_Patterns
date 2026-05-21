#include "RAM.h"
#include "Motherboard.h"

RAM::RAM(const std::string& model, const std::string& type, int capacity, double price)
    : model(model), type(type), capacity(capacity), price(price) {}

std::string RAM::getModel() const { return model; }
double RAM::getBasePrice() const { return price; }
std::string RAM::getType() const { return "RAM"; }
std::string RAM::getRamType() const { return type; }

bool RAM::isCompatibleWith(const Component& other) const {
    if (other.getType() == "Motherboard") {
        const Motherboard* mb = dynamic_cast<const Motherboard*>(&other);
        return mb && mb->getRamType() == type;
    }
    return true;
}