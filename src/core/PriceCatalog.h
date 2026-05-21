#ifndef PRICECATALOG_H
#define PRICECATALOG_H

#include <string>
#include <unordered_map>

class PriceCatalog {
private:
    std::unordered_map<std::string, double> prices;
    PriceCatalog() = default;
    ~PriceCatalog() = default;
    PriceCatalog(const PriceCatalog&) = delete;
    PriceCatalog& operator=(const PriceCatalog&) = delete;

public:
    static PriceCatalog& instance();
    void setPrice(const std::string& model, double price);
    double getPrice(const std::string& model) const;
    void loadDefaults();
};

#endif