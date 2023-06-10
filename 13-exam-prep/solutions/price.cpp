#include "price.h"

Pricing::Pricing(double price, std::string currency) : price(price), currency(currency) {}

double Pricing::getPrice()
{
    return price;
}

std::string Pricing::getCurrency()
{
    return currency;
}

PayNow::PayNow(double price, std::string currency) : Pricing(price, currency) {}

bool PayNow::isPayNow()
{
    return true;
}

bool PayNow::isPayLater()
{
    return false;
}

Pricing *PayNow::clone()
{
    return new PayNow(price, currency);
}

void PayNow::write(std::ostream &out)
{
    out << "pn" << " " << price << " " << currency;
}

void PayNow::read(std::istream &in)
{
    in >> price >> currency;
}

PayLater::PayLater(double price, std::string currency) : Pricing(price, currency) {}

bool PayLater::isPayNow()
{
    return false;
}

bool PayLater::isPayLater()
{
    return true;
}

Pricing *PayLater::clone()
{
    return new PayLater(price, currency);
}

void PayLater::write(std::ostream &out)
{
    out << "pl" << " " << price << " " << currency;
}

void PayLater::read(std::istream &in)
{
    in >> price >> currency;
}
