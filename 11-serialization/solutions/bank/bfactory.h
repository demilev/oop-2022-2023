#pragma once

#include <string>
#include "bank.h"

// "Фабрика" за обекти
BankAccount *factory(std::string objectType);