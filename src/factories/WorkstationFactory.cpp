#include "WorkstationFactory.h"

CPU* WorkstationFactory::createCPU() {
    return new CPU("AMD Ryzen 9 5950X", "AM4", 105, 750.0);
}
Motherboard* WorkstationFactory::createMotherboard() {
    return new Motherboard("ASUS Pro WS X570-ACE", "AM4", "DDR4", 400.0);
}
RAM* WorkstationFactory::createRAM() {
    return new RAM("Kingston ECC 32GB", "DDR4", 32, 200.0);
}
Storage* WorkstationFactory::createStorage() {
    return new Storage("Samsung 970 EVO Plus 2TB", "NVMe", 2000, 250.0);
}
GPU* WorkstationFactory::createGPU() {
    return new GPU("NVIDIA Quadro RTX 4000", 160, 1100.0);
}
PowerSupply* WorkstationFactory::createPowerSupply() {
    return new PowerSupply("Seasonic Prime 850W", 850, 180.0);
}
Cooling* WorkstationFactory::createCooling() {
    return new Cooling("be quiet! Dark Rock Pro 4", "air", 250, 100.0);
}
std::string WorkstationFactory::getPlatformName() const { return "Workstation"; }