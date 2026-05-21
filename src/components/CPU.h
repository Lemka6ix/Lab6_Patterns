#ifndef CPU_H
#define CPU_H

#include "Component.h"

class CPU : public Component {
    std::string model;
    std::string socket;
    int tdp;
    double price;
public:
    CPU(const std::string& model, const std::string& socket, int tdp, double price);
    std::string getModel() const override;
    double getBasePrice() const override;
    bool isCompatibleWith(const Component& other) const override;
    std::string getType() const override;
    std::string getSocket() const;
    int getTDP() const;
};

#endif