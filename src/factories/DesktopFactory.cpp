#include "DesktopFactory.h"

CPU* DesktopFactory::createCPU() {
    return new CPU("Intel Core i7-12700K", "LGA1700", 125, 350.0);
}
Motherboard* DesktopFactory::createMotherboard() {
    return new Motherboard("ASUS ROG Z690", "LGA1700", "DDR4", 250.0);
}
RAM* DesktopFactory::createRAM() {
    return new RAM("Corsair Vengeance LPX 16GB", "DDR4", 16, 80.0);
}
Storage* DesktopFactory::createStorage() {
    return new Storage("Samsung 980 Pro 1TB", "NVMe", 1000, 120.0);
}
GPU* DesktopFactory::createGPU() {
    return new GPU("NVIDIA RTX 3060", 170, 350.0);
}
PowerSupply* DesktopFactory::createPowerSupply() {
    return new PowerSupply("Corsair RM650", 650, 90.0);
}
Cooling* DesktopFactory::createCooling() {
    return new Cooling("Noctua NH-D15", "air", 220, 90.0);
}
std::string DesktopFactory::getPlatformName() const { return "DesktopPC"; }