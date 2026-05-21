#ifndef RAM_H
#define RAM_H

#include "Component.h"

class RAM : public Component {
    std::string model;
    std::string type;
    int capacity;
    double price;
public:
    RAM(const std::string& model, const std::string& type, int capacity, double price);
    std::string getModel() const override;
    double getBasePrice() const override;
    bool isCompatibleWith(const Component& other) const override;
    std::string getType() const override;
    std::string getRamType() const;
};

#endif