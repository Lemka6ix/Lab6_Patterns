#include "CPU.h"
#include "Motherboard.h"

CPU::CPU(const std::string& model, const std::string& socket, int tdp, double price)
    : model(model), socket(socket), tdp(tdp), price(price) {}

std::string CPU::getModel() const { return model; }
double CPU::getBasePrice() const { return price; }
std::string CPU::getType() const { return "CPU"; }
std::string CPU::getSocket() const { return socket; }
int CPU::getTDP() const { return tdp; }

bool CPU::isCompatibleWith(const Component& other) const {
    if (other.getType() == "Motherboard") {
        const Motherboard* mb = dynamic_cast<const Motherboard*>(&other);
        return mb && mb->getSocket() == socket;
    }
    return true;
}