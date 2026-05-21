#ifndef COMPUTERBUILDER_H
#define COMPUTERBUILDER_H

#include "../components/Component.h"
#include "../factories/AbstractFactory.h"
#include <vector>
#include <string>

// Forward declarations
class CPU;
class Motherboard;
class RAM;
class Storage;
class GPU;
class PowerSupply;
class Cooling;

class Computer {
    std::vector<Component*> components;
public:
    ~Computer();
    void addComponent(Component* comp);
    double getTotalPrice() const;
    std::string getSpecification() const;
    std::vector<Component*> getComponents() const { return components; }
};

class ComputerBuilder {
    AbstractComponentFactory* factory;
    CPU* cpu;
    Motherboard* motherboard;
    RAM* ram;
    Storage* storage;
    GPU* gpu;
    PowerSupply* psu;
    Cooling* cooling;
    bool isBuilt;

    bool checkPowerCompatibility() const;
    bool validateCompatibility(Component* newComp) const;
    void clear();

public:
    ComputerBuilder(AbstractComponentFactory* fac);
    ~ComputerBuilder();

    ComputerBuilder& addCPU();
    ComputerBuilder& addMotherboard();
    ComputerBuilder& addRAM();
    ComputerBuilder& addStorage();
    ComputerBuilder& addGPU();
    ComputerBuilder& addPowerSupply();
    ComputerBuilder& addCooling();

    Computer* getResult();
    void reset();
};

#endif