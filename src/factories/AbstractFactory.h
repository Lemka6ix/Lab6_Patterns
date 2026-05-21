#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "../components/CPU.h"
#include "../components/Motherboard.h"
#include "../components/RAM.h"
#include "../components/Storage.h"
#include "../components/GPU.h"
#include "../components/PowerSupply.h"
#include "../components/Cooling.h"

class AbstractComponentFactory {
public:
    virtual ~AbstractComponentFactory() = default;
    virtual CPU* createCPU() = 0;
    virtual Motherboard* createMotherboard() = 0;
    virtual RAM* createRAM() = 0;
    virtual Storage* createStorage() = 0;
    virtual GPU* createGPU() = 0;
    virtual PowerSupply* createPowerSupply() = 0;
    virtual Cooling* createCooling() = 0;
    virtual std::string getPlatformName() const = 0;
};

#endif