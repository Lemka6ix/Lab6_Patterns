#include "Director.h"
#include "ComputerBuilder.h"
#include "../factories/DesktopFactory.h"
#include "../factories/WorkstationFactory.h"
#include "../factories/ServerFactory.h"

Computer* Director::buildGamingPC() {
    DesktopFactory factory;
    ComputerBuilder builder(&factory);
    try {
        builder.addCPU()
               .addMotherboard()
               .addRAM()
               .addStorage()
               .addGPU()
               .addPowerSupply()
               .addCooling();
        return builder.getResult();
    } catch (...) {
        return nullptr;
    }
}

Computer* Director::buildWorkstation() {
    WorkstationFactory factory;
    ComputerBuilder builder(&factory);
    try {
        builder.addCPU()
               .addMotherboard()
               .addRAM()
               .addStorage()
               .addGPU()
               .addPowerSupply()
               .addCooling();
        return builder.getResult();
    } catch (...) {
        return nullptr;
    }
}

Computer* Director::buildServer() {
    ServerFactory factory;
    ComputerBuilder builder(&factory);
    try {
        builder.addCPU()
               .addMotherboard()
               .addRAM()
               .addStorage()
               .addPowerSupply()
               .addCooling();
        return builder.getResult();
    } catch (...) {
        return nullptr;
    }
}