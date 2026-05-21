#include "GPU.h"

GPU::GPU(const std::string& model, int tdp, double price)
    : model(model), tdp(tdp), price(price) {}

std::string GPU::getModel() const { return model; }
double GPU::getBasePrice() const { return price; }
std::string GPU::getType() const { return "GPU"; }
int GPU::getTDP() const { return tdp; }
bool GPU::isCompatibleWith(const Component&) const { return true; }