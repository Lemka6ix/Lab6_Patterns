#ifndef GPU_H
#define GPU_H

#include "Component.h"

class GPU : public Component {
    std::string model;
    int tdp;
    double price;
public:
    GPU(const std::string& model, int tdp, double price);
    std::string getModel() const override;
    double getBasePrice() const override;
    bool isCompatibleWith(const Component& other) const override;
    std::string getType() const override;
    int getTDP() const;
};

#endif