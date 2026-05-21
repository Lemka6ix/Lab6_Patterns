#include "ServerFactory.h"

CPU* ServerFactory::createCPU() {
    return new CPU("Intel Xeon Gold 6226R", "LGA3647", 150, 1800.0);
}
Motherboard* ServerFactory::createMotherboard() {
    return new Motherboard("Supermicro X11DPi-NT", "LGA3647", "DDR4 ECC", 550.0);
}
RAM* ServerFactory::createRAM() {
    return new RAM("Samsung ECC 64GB", "DDR4 ECC", 64, 400.0);
}
Storage* ServerFactory::createStorage() {
    return new Storage("Intel SSD DC P4510 2TB", "NVMe", 2000, 600.0);
}
GPU* ServerFactory::createGPU() {
    return new GPU("NVIDIA Tesla T4", 75, 2500.0);
}
PowerSupply* ServerFactory::createPowerSupply() {
    return new PowerSupply("Delta 1200W PSU", 1200, 300.0);
}
Cooling* ServerFactory::createCooling() {
    return new Cooling("Noctua NH-U12S", "air", 150, 80.0);
}
std::string ServerFactory::getPlatformName() const { return "ServerModule"; }