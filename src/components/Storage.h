#ifndef STORAGE_H
#define STORAGE_H

#include "Component.h"

class Storage : public Component {
    std::string model;
    std::string interface;
    int capacity;
    double price;
public:
    Storage(const std::string& model, const std::string& interface, int capacity, double price);
    std::string getModel() const override;
    double getBasePrice() const override;
    bool isCompatibleWith(const Component& other) const override;
    std::string getType() const override;
};

#endif