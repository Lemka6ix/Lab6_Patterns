#include "PresetStorage.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void PresetStorage::saveToFile(const Preset& preset, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) throw std::runtime_error("Cannot open file for writing");
    file << preset.platform << "\n";
    for (const auto& type : preset.componentTypes) {
        file << type << "\n";
    }
}

Preset PresetStorage::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open file for reading");
    Preset preset;
    std::getline(file, preset.platform);
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) preset.componentTypes.push_back(line);
    }
    return preset;
}