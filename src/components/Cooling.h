#ifndef COOLING_H
#define COOLING_H

#include "Component.h"

class Cooling : public Component {
    std::string model;
    std::string type;
    int tdp;
    double price;
public:
    Cooling(const std::string& model, const std::string& type, int tdp, double price);
    std::string getModel() const override;
    double getBasePrice() const override;
    bool isCompatibleWith(const Component& other) const override;
    std::string getType() const override;
};

#endif