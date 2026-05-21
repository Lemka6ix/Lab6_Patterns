#include "Motherboard.h"
#include "CPU.h"
#include "RAM.h"

Motherboard::Motherboard(const std::string& model, const std::string& socket, const std::string& ramType, double price)
    : model(model), socket(socket), ramType(ramType), price(price) {}

std::string Motherboard::getModel() const { return model; }
double Motherboard::getBasePrice() const { return price; }
std::string Motherboard::getType() const { return "Motherboard"; }
std::string Motherboard::getSocket() const { return socket; }
std::string Motherboard::getRamType() const { return ramType; }

bool Motherboard::isCompatibleWith(const Component& other) const {
    if (other.getType() == "CPU") {
        const CPU* cpu = dynamic_cast<const CPU*>(&other);
        return cpu && cpu->getSocket() == socket;
    }
    if (other.getType() == "RAM") {
        const RAM* ram = dynamic_cast<const RAM*>(&other);
        return ram && ram->getRamType() == ramType;
    }
    return true;
}