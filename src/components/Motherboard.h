#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include "Component.h"

class Motherboard : public Component {
    std::string model;
    std::string socket;
    std::string ramType;
    double price;
public:
    Motherboard(const std::string& model, const std::string& socket, const std::string& ramType, double price);
    std::string getModel() const override;
    double getBasePrice() const override;
    bool isCompatibleWith(const Component& other) const override;
    std::string getType() const override;
    std::string getSocket() const;
    std::string getRamType() const;
};

#endif