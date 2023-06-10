#include "catalogue.h"

Catalogue::ItemWithPricing::ItemWithPricing(std::string id, Pricing *pricing) : id(id), pricing(pricing) {}

void Catalogue::cleanup()
{
    for (ItemWithPricing item : items)
    {
        delete item.pricing;
    }
}

void Catalogue::copy(const Catalogue &other)
{
    items = std::vector<ItemWithPricing>();
    for (ItemWithPricing item : other.items)
    {
        addProduct(item.id, item.pricing);
    }
}

Catalogue::Catalogue() {}

Catalogue::Catalogue(const Catalogue &other)
{
    copy(other);
}

Catalogue &Catalogue::operator=(const Catalogue &other)
{
    if (this != &other)
    {
        cleanup();
        copy(other);
    }

    return *this;
}

Catalogue::~Catalogue()
{
    cleanup();
}

void Catalogue::addProduct(std::string id, Pricing *pricing)
{

    items.push_back(ItemWithPricing(id, pricing->clone()));
}

Pricing *factory(std::string objectType)
{   
    if (objectType == "pn")
    {
        return new PayNow(0, "USD");
    }

    if (objectType == "pl")
    {
        return new PayLater(0, "USD");
    }

    throw std::runtime_error("Unknown prcing type " + objectType);

    return nullptr;
}

std::ostream &operator<<(std::ostream &out, const Catalogue &c)
{

    for (int i = 0; i < c.items.size(); i++)
    {
        out << c.items[i].id << " ";
        c.items[i].pricing->write(out);
        out << " ";
    }

    return out;
}

std::istream &operator>>(std::istream &in, Catalogue &c)
{
    Catalogue result;
    std::string objectId;
    std::string objectType;
    while (in >> objectId >> objectType)
    {
        Pricing *pricing = factory(objectType);
        
        pricing->read(in);
        
        result.addProduct(objectId, pricing);
        
        delete pricing;
    }

    c = result;

    return in;
}