#pragma once

#include <vector>

#include "price.h"

class Catalogue
{
private:
    struct ItemWithPricing
    {
        Pricing * pricing;
        std::string id;

        ItemWithPricing(std::string, Pricing *);
    };

    std::vector<ItemWithPricing> items;

    void cleanup();
    void copy(const Catalogue&);
public:
    Catalogue();
    Catalogue(const Catalogue&);
    Catalogue& operator=(const Catalogue&);
    ~Catalogue();

    void addProduct(std::string, Pricing*);

    friend std::ostream &operator<<(std::ostream &, const Catalogue &);
};

std::istream &operator>>(std::istream &, Catalogue &);