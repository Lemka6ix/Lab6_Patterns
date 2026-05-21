#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component {
public:
    virtual ~Component() = default;
    virtual std::string getModel() const = 0;
    virtual double getBasePrice() const = 0;
    virtual bool isCompatibleWith(const Component& other) const = 0;
    virtual std::string getType() const = 0;
};

#endif