#ifndef ENTITYCLASS_GUARD
#define ENTITYCLASS_GUARD

#include <iostream>
#include <array>
#include <memory>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include "Item.hpp"
#include "validInput.hpp"

class EntityClass       // Base class for player and enemies
{
public:
    using item_ptr = std::shared_ptr<Item>;
protected:
    std::string m_name;
    int m_hitPointStats;
    int m_currentHP;
    int m_level;
    double m_experiencePoints;
    double m_experiencePointsLimit;
    int m_attack;
    int m_defence;
    int m_quickness;
    int m_weightStat;
    int m_currentWeight;
    int m_gold;
    std::array<std::pair<Item_::item_t, item_ptr>, 3> m_equipment 
    { { 
        {Item_::swordFlag, nullptr },
        {Item_::armorFlag, nullptr},
        {Item_::necklaceFlag, nullptr} 
    } };
    std::vector<item_ptr> m_inventory {};

public:
    EntityClass(std::string name = "", int hitPointStats = 10, 
    int level = 1, int attack = 10, int defence = 10, 
    int quickness = 10, int weightStat = 10, int gold = 0);
    
    ~EntityClass();

    int getHitpointStats();
    int getCurrentHP();
    int getLevel();
    int getAttack();
    int getDefence();
    int getQuickness();
    int getWeightStat();
    int getGold();
    int getCurrentWeight();
    const std::string_view getName();
    double getExperiencePoints();
    double getExperiencePointsLimit();
    EntityClass& displayStats();
    EntityClass& displayInventory();
    EntityClass& displayItemInfo();
    EntityClass& displayEquipment();
    EntityClass& displayEquipmentInfo();
    EntityClass& increaseExperience( int increase = 0 );
    bool ifLeveledUp();
    EntityClass& takeDamage(int damage = 0);
    EntityClass& rest();
    bool checkDead();
    EntityClass& levelUp();
    EntityClass& buyOrTakeItem(Item * item, int reduction = 0);
    EntityClass& increaseGold(int increase = 0);
    int attack();
    int speed();
    EntityClass& equipItem();
    EntityClass& unequipItem();
    EntityClass& dropItem();

};

#endif