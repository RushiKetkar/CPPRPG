#ifndef GAMEPLAY_GUARD
#define GAMEPLAY_GUARD

#include "Player.hpp"
#include "Monster.hpp"
#include "validInput.hpp"

bool fight( const std::unique_ptr<Player>& player );
void buyOrSell( const std::unique_ptr<Player>& player );
bool fightFinalBoss( const std::unique_ptr<Player>& player );
void rest( const std::unique_ptr<Player>& player );
void savePlayer( const std::unique_ptr<Player>& player );
bool gameplay( const std::unique_ptr<Player>& player );
bool quit();
void manageEquipment( const std::unique_ptr<Player>& player );
std::unique_ptr<Player> createOrLoadPlayer();

#endif