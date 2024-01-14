#ifndef PLAYER_GUARD
#define PLAYER_GUARD

#include <fstream>
#include <sstream>

#include "EntityBase.hpp"

class Player : public EntityClass
{
public:
    Player(const std::string& fileName);

    Player();

    Player& saveCharacter();
};

#endif