#pragma once

#include <string>
#include <fstream>

class Pricing
{
protected:
    double price;
    std::string currency;

public:
    Pricing(double, std::string);
    virtual ~Pricing() = default;
    virtual bool isPayNow() = 0;
    virtual bool isPayLater() = 0;
    virtual Pricing* clone() = 0;
    virtual void write(std::ostream &) = 0;
    virtual void read(std::istream &) = 0;

    double getPrice();
    std::string getCurrency();
};

class PayNow : public Pricing
{
public:
    PayNow(double, std::string);
    bool isPayNow();
    bool isPayLater();
    Pricing* clone();
    void write(std::ostream &);
    void read(std::istream &);
};

class PayLater : public Pricing
{
public:
    PayLater(double, std::string);
    bool isPayNow();
    bool isPayLater();
    Pricing* clone();
    void write(std::ostream &);
    void read(std::istream &);
};