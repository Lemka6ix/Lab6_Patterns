#ifndef WORKSTATIONFACTORY_H
#define WORKSTATIONFACTORY_H

#include "AbstractFactory.h"

class WorkstationFactory : public AbstractComponentFactory {
public:
    CPU* createCPU() override;
    Motherboard* createMotherboard() override;
    RAM* createRAM() override;
    Storage* createStorage() override;
    GPU* createGPU() override;
    PowerSupply* createPowerSupply() override;
    Cooling* createCooling() override;
    std::string getPlatformName() const override;
};

#endif