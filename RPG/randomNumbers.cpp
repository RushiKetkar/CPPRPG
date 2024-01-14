#include "randomNumber.hpp"

int getRandomNumber( int min, int max )
{
    static std::mt19937_64 randomnumber{ std::random_device{}() };

    std::uniform_int_distribution range{ min, max };

    return range( randomnumber );
}