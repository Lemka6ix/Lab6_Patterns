#include "PriceCatalog.h"

PriceCatalog& PriceCatalog::instance() {
    static PriceCatalog instance;
    return instance;
}

void PriceCatalog::setPrice(const std::string& model, double price) {
    prices[model] = price;
}

double PriceCatalog::getPrice(const std::string& model) const {
    auto it = prices.find(model);
    if (it != prices.end()) return it->second;
    return 0.0;
}

void PriceCatalog::loadDefaults() {
    // Desktop
    setPrice("Intel Core i7-12700K", 350.0);
    setPrice("ASUS ROG Z690", 250.0);
    setPrice("Corsair Vengeance LPX 16GB", 80.0);
    setPrice("Samsung 980 Pro 1TB", 120.0);
    setPrice("NVIDIA RTX 3060", 350.0);
    setPrice("Corsair RM650", 90.0);
    setPrice("Noctua NH-D15", 90.0);
    // Workstation
    setPrice("AMD Ryzen 9 5950X", 750.0);
    setPrice("ASUS Pro WS X570-ACE", 400.0);
    setPrice("Kingston ECC 32GB", 200.0);
    setPrice("Samsung 970 EVO Plus 2TB", 250.0);
    setPrice("NVIDIA Quadro RTX 4000", 1100.0);
    setPrice("Seasonic Prime 850W", 180.0);
    setPrice("be quiet! Dark Rock Pro 4", 100.0);
    // Server
    setPrice("Intel Xeon Gold 6226R", 1800.0);
    setPrice("Supermicro X11DPi-NT", 550.0);
    setPrice("Samsung ECC 64GB", 400.0);
    setPrice("Intel SSD DC P4510 2TB", 600.0);
    setPrice("NVIDIA Tesla T4", 2500.0);
    setPrice("Delta 1200W PSU", 300.0);
    setPrice("Noctua NH-U12S", 80.0);
}