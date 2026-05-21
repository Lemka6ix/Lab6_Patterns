#ifndef POWERSUPPLY_H
#define POWERSUPPLY_H

#include "Component.h"

class PowerSupply : public Component {
    std::string model;
    int wattage;
    double price;
public:
    PowerSupply(const std::string& model, int wattage, double price);
    std::string getModel() const override;
    double getBasePrice() const override;
    bool isCompatibleWith(const Component& other) const override;
    std::string getType() const override;
    int getWattage() const;
};

#endif