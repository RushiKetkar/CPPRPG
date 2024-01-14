#ifndef ENTITYCLASS_GUARD
#define ENTITYCLASS_GUARD

#include <iostream>
#include <array>
#include <memory>
#include <map>
#include <string>
#include <algorithm>
#include "Status.hpp"
#include "Item.hpp"
#include "RoundPass.hpp"
#include "validInput.hpp"

class EntityClass       // Base class for player and enemies
{
public:
    using status_ptr = std::unique_ptr<Status>;
    using item_ptr = std::unique_ptr<Item>;
protected:
    std::string m_name;
    int m_hitPoints;
    int m_level;
    int m_attack;
    int m_defence;
    int m_quickness;
    int m_weight;
    int m_magicAffinity;
    int m_currentWeight;
    int m_gold;
    std::map<int, status_ptr> m_statusList {};
    std::array<item_ptr, 3> m_equip {};
    std::map<int, item_ptr> m_inventory {};
    ItemFlags::item_t m_itemFlags;

public:
    EntityClass(std::string name = "", int hitPoints = 10, 
    int level = 1, int attack = 10, int defence = 10, 
    int quickness = 10, int weight = 10, int magicAffinity = 10,
    ItemFlags::item_t itemFlags = 0, int currentWeight = 0,
    int gold = 0);
    
    ~EntityClass();

    int getHitpoints();
    int getLevel();
    int getAttack();
    int getDefence();
    int getQuickness();
    int getWeight();
    int getMagicAffinity();
    int getGold();
    EntityClass& examine();
    EntityClass& takeDamage(int damage = 0);
    EntityClass& heal(int increase = 0);
    bool checkDead();
    EntityClass& cureStatus(const StatusConstants::status_t& type);
    EntityClass& inflictStatus(status_ptr& status);
    EntityClass& levelUp();
    EntityClass& checkStatus();
    bool checkEquip();
    EntityClass& buyItem(item_ptr& item, int reduction = 0);
    EntityClass& increaseGold(int increase = 0);
    int attack();
    EntityClass& useItem(const item_ptr& item);
    EntityClass& equipItem(const item_ptr& item);
    EntityClass& unequipItem(const item_ptr& item);
    EntityClass& takeItem(const item_ptr& item);
    EntityClass& dropItem(const item_ptr& item);
    bool ifItemSlotFull(const ItemFlags::item_t& flag);
    EntityClass& statusReduce();


};

#endif