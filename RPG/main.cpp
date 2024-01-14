#include "gameplay.hpp"

int main(int argc, char const *argv[])
{
    auto player{ createOrLoadPlayer() };

    while ( gameplay( player ) )
    {
    }
    
    std::cout << "\nHave a wonderful day!\n";

    return 0;
}
