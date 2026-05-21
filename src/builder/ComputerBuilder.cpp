#include "ComputerBuilder.h"
#include "../core/PriceCatalog.h"
#include "../components/CPU.h"
#include "../components/GPU.h"
#include "../components/Motherboard.h"
#include "../components/RAM.h"
#include "../components/Storage.h"
#include "../components/PowerSupply.h"
#include "../components/Cooling.h"
#include <iostream>
#include <stdexcept>

Computer::~Computer() {
    for (auto comp : components) delete comp;
}

void Computer::addComponent(Component* comp) {
    components.push_back(comp);
}

double Computer::getTotalPrice() const {
    double total = 0.0;
    for (auto comp : components) {
        total += PriceCatalog::instance().getPrice(comp->getModel());
    }
    return total;
}

std::string Computer::getSpecification() const {
    std::string spec;
    for (auto comp : components) {
        spec += comp->getType() + ": " + comp->getModel() + "\n";
    }
    return spec;
}

ComputerBuilder::ComputerBuilder(AbstractComponentFactory* fac)
    : factory(fac), cpu(nullptr), motherboard(nullptr), ram(nullptr), storage(nullptr),
      gpu(nullptr), psu(nullptr), cooling(nullptr), isBuilt(false) {}

ComputerBuilder::~ComputerBuilder() {
    clear();
}

void ComputerBuilder::clear() {
    delete cpu; cpu = nullptr;
    delete motherboard; motherboard = nullptr;
    delete ram; ram = nullptr;
    delete storage; storage = nullptr;
    delete gpu; gpu = nullptr;
    delete psu; psu = nullptr;
    delete cooling; cooling = nullptr;
    isBuilt = false;
}

bool ComputerBuilder::validateCompatibility(Component* newComp) const {
    if (!newComp) return true;
    Component* existing[] = {cpu, motherboard, ram, storage, gpu, psu, cooling};
    for (auto comp : existing) {
        if (comp && !newComp->isCompatibleWith(*comp)) return false;
        if (comp && !comp->isCompatibleWith(*newComp)) return false;
    }
    return true;
}

bool ComputerBuilder::checkPowerCompatibility() const {
    if (!psu) return true;
    int totalTDP = 0;
    if (cpu) totalTDP += cpu->getTDP();
    if (gpu) totalTDP += gpu->getTDP();
    return psu->getWattage() >= totalTDP + 50;
}

ComputerBuilder& ComputerBuilder::addCPU() {
    if (cpu) throw std::logic_error("CPU already added");
    CPU* newCpu = factory->createCPU();
    if (!validateCompatibility(newCpu)) {
        delete newCpu;
        throw std::runtime_error("Incompatible CPU");
    }
    cpu = newCpu;
    return *this;
}

ComputerBuilder& ComputerBuilder::addMotherboard() {
    if (motherboard) throw std::logic_error("Motherboard already added");
    Motherboard* newMb = factory->createMotherboard();
    if (!validateCompatibility(newMb)) {
        delete newMb;
        throw std::runtime_error("Incompatible Motherboard");
    }
    motherboard = newMb;
    return *this;
}

ComputerBuilder& ComputerBuilder::addRAM() {
    if (ram) throw std::logic_error("RAM already added");
    RAM* newRam = factory->createRAM();
    if (!validateCompatibility(newRam)) {
        delete newRam;
        throw std::runtime_error("Incompatible RAM");
    }
    ram = newRam;
    return *this;
}

ComputerBuilder& ComputerBuilder::addStorage() {
    if (storage) throw std::logic_error("Storage already added");
    storage = factory->createStorage();
    if (!validateCompatibility(storage)) {
        delete storage; storage = nullptr;
        throw std::runtime_error("Incompatible Storage");
    }
    return *this;
}

ComputerBuilder& ComputerBuilder::addGPU() {
    if (gpu) throw std::logic_error("GPU already added");
    gpu = factory->createGPU();
    if (!validateCompatibility(gpu)) {
        delete gpu; gpu = nullptr;
        throw std::runtime_error("Incompatible GPU");
    }
    return *this;
}

ComputerBuilder& ComputerBuilder::addPowerSupply() {
    if (psu) throw std::logic_error("PSU already added");
    psu = factory->createPowerSupply();
    if (!validateCompatibility(psu)) {
        delete psu; psu = nullptr;
        throw std::runtime_error("Incompatible Power Supply");
    }
    if (!checkPowerCompatibility()) {
        delete psu; psu = nullptr;
        throw std::runtime_error("Power supply insufficient wattage");
    }
    return *this;
}

ComputerBuilder& ComputerBuilder::addCooling() {
    if (cooling) throw std::logic_error("Cooling already added");
    cooling = factory->createCooling();
    if (!validateCompatibility(cooling)) {
        delete cooling; cooling = nullptr;
        throw std::runtime_error("Incompatible Cooling");
    }
    return *this;
}

Computer* ComputerBuilder::getResult() {
    if (isBuilt) throw std::logic_error("Computer already built from this builder");
    if (!cpu || !motherboard || !ram || !storage || !psu) {
        throw std::runtime_error("Missing essential components (CPU, MB, RAM, Storage, PSU)");
    }
    if (!checkPowerCompatibility()) {
        throw std::runtime_error("Total power exceeds PSU capacity");
    }
    Computer* computer = new Computer();
    if (cpu) computer->addComponent(cpu); cpu = nullptr;
    if (motherboard) computer->addComponent(motherboard); motherboard = nullptr;
    if (ram) computer->addComponent(ram); ram = nullptr;
    if (storage) computer->addComponent(storage); storage = nullptr;
    if (gpu) computer->addComponent(gpu); gpu = nullptr;
    if (psu) computer->addComponent(psu); psu = nullptr;
    if (cooling) computer->addComponent(cooling); cooling = nullptr;
    isBuilt = true;
    return computer;
}

void ComputerBuilder::reset() {
    clear();
    isBuilt = false;
}