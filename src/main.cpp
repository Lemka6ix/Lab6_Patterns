#include "builder/ComputerBuilder.h"
#include "builder/Director.h"
#include "factories/DesktopFactory.h"
#include "factories/WorkstationFactory.h"
#include "factories/ServerFactory.h"
#include "core/PriceCatalog.h"
#include "storage/PresetStorage.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Простая функция для вывода результата теста
static void runTest(const std::string& name, void (*testFunc)()) {
    std::cout << "Test " << name << ": ";
    try {
        testFunc();
        std::cout << "OK" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "ERROR: unknown exception" << std::endl;
    }
}

// Демонстрация работы
void demo() {
    std::cout << "\n=== Демонстрация конфигуратора ===\n";
    
    std::cout << "\n--- Desktop PC (ручная сборка) ---\n";
    DesktopFactory deskFac;
    ComputerBuilder builder(&deskFac);
    try {
        builder.addCPU()
               .addMotherboard()
               .addRAM()
               .addStorage()
               .addGPU()
               .addPowerSupply()
               .addCooling();
        Computer* pc = builder.getResult();
        std::cout << "Спецификация:\n" << pc->getSpecification();
        std::cout << "Общая стоимость: $" << pc->getTotalPrice() << std::endl;
        delete pc;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    
    std::cout << "\n--- Workstation (Director) ---\n";
    Director director;
    Computer* ws = director.buildWorkstation();
    if (ws) {
        std::cout << "Спецификация Workstation:\n" << ws->getSpecification();
        std::cout << "Стоимость: $" << ws->getTotalPrice() << std::endl;
        delete ws;
    } else {
        std::cout << "Не удалось собрать Workstation\n";
    }
    
    std::cout << "\n--- Server Module (Director) ---\n";
    Computer* srv = director.buildServer();
    if (srv) {
        std::cout << "Спецификация Server:\n" << srv->getSpecification();
        std::cout << "Стоимость: $" << srv->getTotalPrice() << std::endl;
        delete srv;
    } else {
        std::cout << "Не удалось собрать Server\n";
    }
    
    Preset preset;
    preset.platform = "DesktopPC";
    preset.componentTypes = {"CPU","Motherboard","RAM","Storage","GPU","PowerSupply","Cooling"};
    PresetStorage::saveToFile(preset, "gaming_preset.txt");
    std::cout << "\nПресет сохранён в gaming_preset.txt\n";
    
    std::cout << "\n--- Загрузка пресета и сборка ---\n";
    Preset loaded = PresetStorage::loadFromFile("gaming_preset.txt");
    std::cout << "Загружена платформа: " << loaded.platform << "\n";
    AbstractComponentFactory* fac = nullptr;
    if (loaded.platform == "DesktopPC") fac = new DesktopFactory();
    else if (loaded.platform == "Workstation") fac = new WorkstationFactory();
    else if (loaded.platform == "ServerModule") fac = new ServerFactory();
    if (fac) {
        ComputerBuilder builder2(fac);
        try {
            for (const auto& type : loaded.componentTypes) {
                if (type == "CPU") builder2.addCPU();
                else if (type == "Motherboard") builder2.addMotherboard();
                else if (type == "RAM") builder2.addRAM();
                else if (type == "Storage") builder2.addStorage();
                else if (type == "GPU") builder2.addGPU();
                else if (type == "PowerSupply") builder2.addPowerSupply();
                else if (type == "Cooling") builder2.addCooling();
            }
            Computer* comp = builder2.getResult();
            std::cout << "Собран компьютер из пресета:\n" << comp->getSpecification();
            std::cout << "Стоимость: $" << comp->getTotalPrice() << std::endl;
            delete comp;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка сборки из пресета: " << e.what() << std::endl;
        }
        delete fac;
    }
}

// Тесты
static void test_DirectorBuildsWorkstation() {
    Director dir;
    Computer* ws = dir.buildWorkstation();
    if (!ws) throw std::runtime_error("Build failed");
    if (ws->getTotalPrice() <= 0) throw std::runtime_error("Invalid price");
    delete ws;
}

static void test_IncompatibleCPUAndMotherboard() {
    DesktopFactory deskFac;
    WorkstationFactory workFac;
    CPU* cpu = deskFac.createCPU();
    Motherboard* mb = workFac.createMotherboard();
    bool compatible = cpu->isCompatibleWith(*mb) && mb->isCompatibleWith(*cpu);
    delete cpu;
    delete mb;
    if (compatible) throw std::runtime_error("Expected incompatibility but passed");
}

static void test_PriceCalculation() {
    DesktopFactory fac;
    ComputerBuilder builder(&fac);
    builder.addCPU().addMotherboard().addRAM().addStorage().addPowerSupply();
    Computer* comp = builder.getResult();
    double price = comp->getTotalPrice();
    delete comp;
    if (price <= 0) throw std::runtime_error("Price zero or negative");
}

static void test_SaveAndLoadPreset() {
    Preset original;
    original.platform = "DesktopPC";
    std::vector<std::string> types = {"CPU","MB","RAM"};
    original.componentTypes = types;
    PresetStorage::saveToFile(original, "test_preset.txt");
    Preset loaded = PresetStorage::loadFromFile("test_preset.txt");
    if (loaded.platform != original.platform) throw std::runtime_error("Platform mismatch");
    if (loaded.componentTypes.size() != original.componentTypes.size()) throw std::runtime_error("Component count mismatch");
}

static void test_BuilderResetAndRebuild() {
    DesktopFactory fac;
    ComputerBuilder builder(&fac);
    builder.addCPU().addMotherboard().addRAM();
    builder.reset();
    builder.addCPU().addMotherboard().addRAM().addStorage().addPowerSupply();
    Computer* comp = builder.getResult();
    if (!comp) throw std::runtime_error("Rebuild failed");
    delete comp;
}

void runTests() {
    std::cout << "\n=== Запуск тестов ===\n";
    PriceCatalog::instance().loadDefaults();
    runTest("Director builds Workstation", test_DirectorBuildsWorkstation);
    runTest("Incompatible CPU and Motherboard", test_IncompatibleCPUAndMotherboard);
    runTest("Price calculation", test_PriceCalculation);
    runTest("Save and load preset", test_SaveAndLoadPreset);
    runTest("Builder reset and rebuild", test_BuilderResetAndRebuild);
}

int main() {
    PriceCatalog::instance().loadDefaults();
    demo();
    runTests();
    return 0;
}