#include <iostream>
#include <limits>

#include "validInput.hpp"

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

