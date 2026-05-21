#ifndef PRESETSTORAGE_H
#define PRESETSTORAGE_H

#include <string>
#include <vector>

struct Preset {
    std::string platform; // "DesktopPC", "Workstation", "ServerModule"
    std::vector<std::string> componentTypes; // список добавленных типов: "CPU","MB","RAM","Storage","GPU","PSU","Cooling"
};

class PresetStorage {
public:
    static void saveToFile(const Preset& preset, const std::string& filename);
    static Preset loadFromFile(const std::string& filename);
};

#endif