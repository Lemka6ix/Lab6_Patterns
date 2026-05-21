/**
 * @file main.cpp
 * @brief Точка входа в программу. Демонстрация и тестирование.
 */
/**
 * @file main.cpp
 * @brief Interactive computer configurator with Builder, Abstract Factory, Singleton.
 */

#include "builder/ComputerBuilder.h"
#include "builder/Director.h"
#include "factories/DesktopFactory.h"
#include "factories/WorkstationFactory.h"
#include "factories/ServerFactory.h"
#include "core/PriceCatalog.h"
#include "storage/PresetStorage.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <memory>

// Helper: clear input buffer
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Helper: print computer info
void printComputer(const Computer* comp) {
    if (!comp) {
        std::cout << "No computer built.\n";
        return;
    }
    std::cout << "\n=== SPECIFICATION ===\n";
    std::cout << comp->getSpecification();
    std::cout << "Total price: $" << comp->getTotalPrice() << "\n";
    std::cout << "=====================\n\n";
}

// Helper: select platform
AbstractComponentFactory* selectPlatform() {
    int choice;
    std::cout << "\nSelect platform:\n";
    std::cout << "1. Desktop PC (gaming/home)\n";
    std::cout << "2. Workstation (professional)\n";
    std::cout << "3. Server module\n";
    std::cout << "Enter number: ";
    std::cin >> choice;
    clearInput();

    switch (choice) {
        case 1: return new DesktopFactory();
        case 2: return new WorkstationFactory();
        case 3: return new ServerFactory();
        default:
            std::cout << "Invalid, using Desktop PC.\n";
            return new DesktopFactory();
    }
}

// Builder step-by-step assembly
Computer* buildStepByStep(AbstractComponentFactory* factory) {
    ComputerBuilder builder(factory);
    std::string answer;

    std::cout << "\n--- Step-by-step assembly ---\n";
    std::cout << "Add CPU? (y/n): ";
    std::cin >> answer;
    if (answer == "y" || answer == "Y") {
        try { builder.addCPU(); std::cout << "CPU added.\n"; }
        catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
    }

    std::cout << "Add Motherboard? (y/n): ";
    std::cin >> answer;
    if (answer == "y" || answer == "Y") {
        try { builder.addMotherboard(); std::cout << "Motherboard added.\n"; }
        catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
    }

    std::cout << "Add RAM? (y/n): ";
    std::cin >> answer;
    if (answer == "y" || answer == "Y") {
        try { builder.addRAM(); std::cout << "RAM added.\n"; }
        catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
    }

    std::cout << "Add Storage? (y/n): ";
    std::cin >> answer;
    if (answer == "y" || answer == "Y") {
        try { builder.addStorage(); std::cout << "Storage added.\n"; }
        catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
    }

    std::cout << "Add GPU? (y/n): ";
    std::cin >> answer;
    if (answer == "y" || answer == "Y") {
        try { builder.addGPU(); std::cout << "GPU added.\n"; }
        catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
    }

    std::cout << "Add Power Supply? (y/n): ";
    std::cin >> answer;
    if (answer == "y" || answer == "Y") {
        try { builder.addPowerSupply(); std::cout << "Power Supply added.\n"; }
        catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
    }

    std::cout << "Add Cooling? (y/n): ";
    std::cin >> answer;
    if (answer == "y" || answer == "Y") {
        try { builder.addCooling(); std::cout << "Cooling added.\n"; }
        catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
    }

    try {
        return builder.getResult();
    } catch (const std::exception& e) {
        std::cout << "Build failed: " << e.what() << "\n";
        return nullptr;
    }
}

// Save current computer as preset
void savePreset(Computer* comp, const std::string& platformName) {
    if (!comp) {
        std::cout << "No computer to save.\n";
        return;
    }
    Preset preset;
    preset.platform = platformName;
    // Store component types (simple approach)
    preset.componentTypes.clear();
    auto components = comp->getComponents();
    for (auto* c : components) {
        preset.componentTypes.push_back(c->getType());
    }
    std::string filename;
    std::cout << "Enter preset filename: ";
    std::cin >> filename;
    try {
        PresetStorage::saveToFile(preset, filename);
        std::cout << "Preset saved to " << filename << "\n";
    } catch (const std::exception& e) {
        std::cout << "Save error: " << e.what() << "\n";
    }
}

// Load preset and build computer
Computer* loadPreset(AbstractComponentFactory* factory) {
    std::string filename;
    std::cout << "Enter preset filename: ";
    std::cin >> filename;
    Preset preset;
    try {
        preset = PresetStorage::loadFromFile(filename);
    } catch (const std::exception& e) {
        std::cout << "Load error: " << e.what() << "\n";
        return nullptr;
    }
    std::cout << "Loaded platform: " << preset.platform << "\n";
    // Rebuild by adding components in the same order
    ComputerBuilder builder(factory);
    for (const auto& type : preset.componentTypes) {
        try {
            if (type == "CPU") builder.addCPU();
            else if (type == "Motherboard") builder.addMotherboard();
            else if (type == "RAM") builder.addRAM();
            else if (type == "Storage") builder.addStorage();
            else if (type == "GPU") builder.addGPU();
            else if (type == "PowerSupply") builder.addPowerSupply();
            else if (type == "Cooling") builder.addCooling();
        } catch (const std::exception& e) {
            std::cout << "Warning: could not add " << type << " - " << e.what() << "\n";
        }
    }
    try {
        return builder.getResult();
    } catch (const std::exception& e) {
        std::cout << "Build from preset failed: " << e.what() << "\n";
        return nullptr;
    }
}

int main() {
    // Load default prices (Singleton pattern)
    PriceCatalog::instance().loadDefaults();

    std::cout << "========================================\n";
    std::cout << "   COMPUTER CONFIGURATOR v1.0\n";
    std::cout << "========================================\n";

    AbstractComponentFactory* factory = nullptr;
    Computer* currentComputer = nullptr;
    std::string platformName;

    while (true) {
        std::cout << "\n--- MAIN MENU ---\n";
        std::cout << "1. Choose platform (Desktop/Workstation/Server)\n";
        std::cout << "2. Build computer step-by-step (Builder pattern)\n";
        std::cout << "3. Build predefined configuration (Director)\n";
        std::cout << "4. Show current computer specification\n";
        std::cout << "5. Save current configuration as preset\n";
        std::cout << "6. Load preset and build\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        int choice;
        std::cin >> choice;
        clearInput();

        switch (choice) {
            case 1: {
                delete factory;
                factory = selectPlatform();
                platformName = factory->getPlatformName();
                std::cout << "Platform set to: " << platformName << "\n";
                // reset current computer because platform changed
                delete currentComputer;
                currentComputer = nullptr;
                break;
            }
            case 2: {
                if (!factory) {
                    std::cout << "First select platform (option 1).\n";
                    break;
                }
                delete currentComputer;
                currentComputer = buildStepByStep(factory);
                if (currentComputer) {
                    std::cout << "\nBuild successful!\n";
                    printComputer(currentComputer);
                }
                break;
            }
            case 3: {
                if (!factory) {
                    std::cout << "First select platform (option 1).\n";
                    break;
                }
                delete currentComputer;
                Director director;
                std::cout << "Predefined configs:\n";
                std::cout << "a) Gaming PC (Desktop)\n";
                std::cout << "b) Workstation\n";
                std::cout << "c) Server\n";
                std::cout << "Enter letter: ";
                char cfg;
                std::cin >> cfg;
                clearInput();
                if (cfg == 'a') {
                    // But Director methods create new factory internally, so we must use current factory's platform?
                    // Better: use Director only for the platform already selected.
                    // We'll call appropriate director method based on platformName.
                    if (platformName == "DesktopPC")
                        currentComputer = director.buildGamingPC();
                    else if (platformName == "Workstation")
                        currentComputer = director.buildWorkstation();
                    else
                        currentComputer = director.buildServer();
                } else if (cfg == 'b') {
                    currentComputer = director.buildWorkstation();
                } else if (cfg == 'c') {
                    currentComputer = director.buildServer();
                } else {
                    std::cout << "Invalid.\n";
                    break;
                }
                if (currentComputer) {
                    std::cout << "Predefined computer built.\n";
                    printComputer(currentComputer);
                } else {
                    std::cout << "Failed to build predefined computer.\n";
                }
                break;
            }
            case 4: {
                if (currentComputer)
                    printComputer(currentComputer);
                else
                    std::cout << "No computer built yet.\n";
                break;
            }
            case 5: {
                if (currentComputer && factory)
                    savePreset(currentComputer, platformName);
                else
                    std::cout << "No computer to save.\n";
                break;
            }
            case 6: {
                if (!factory) {
                    std::cout << "First select platform (option 1).\n";
                    break;
                }
                delete currentComputer;
                currentComputer = loadPreset(factory);
                if (currentComputer) {
                    std::cout << "Loaded and built from preset.\n";
                    printComputer(currentComputer);
                }
                break;
            }
            case 0:
                delete factory;
                delete currentComputer;
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}