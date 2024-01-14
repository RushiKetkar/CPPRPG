#include "EntityBase.hpp"

EntityClass::EntityClass(std::string name, int hitPointStats,
int level, int attack, int defence, int quickness, 
int weightStat,
int gold) : m_attack{ attack }, 
m_defence{ defence }, m_hitPointStats{ hitPointStats }, 
m_level{ level }, m_currentHP{ m_hitPointStats },
m_quickness{ quickness }, m_weightStat{ weightStat },
m_name{ name }, m_currentWeight{ 0 },
m_gold{ gold }, m_experiencePoints{ 0 }, m_experiencePointsLimit{ 20 }
{  }

EntityClass::~EntityClass() {}

// Getters
int EntityClass::getHitpointStats() { return m_hitPointStats; }
int EntityClass::getCurrentHP() { return m_currentHP; }
int EntityClass::getDefence() { return m_defence; }
int EntityClass::getAttack() { return m_attack; }
int EntityClass::getLevel() { return m_level; }
int EntityClass::getQuickness() { return m_quickness; }
int EntityClass::getWeightStat() { return m_weightStat; }
int EntityClass::getGold() { return m_gold; }
int EntityClass::getCurrentWeight() { return m_currentWeight; }
const std::string_view EntityClass::getName() { return m_name; }
double EntityClass::getExperiencePoints() { return m_experiencePoints; }
double EntityClass::getExperiencePointsLimit() { return m_experiencePointsLimit; }

// Displays
EntityClass& EntityClass::displayStats()
{
    std::cout << "Name(N): " << m_name << '\n';
    std::cout << "Health(H): " << m_hitPointStats << '\n';
    std::cout << "Defence(D): " << m_defence << '\n';
    std::cout << "Attack Power(A): " << m_attack << '\n';
    std::cout << "Level(L): " << m_level << '\n';
    std::cout << "Quickness(Q): " << m_quickness << '\n';
    std::cout << "Weight(W): " << m_weightStat << '\n';
    std::cout << "Experience Points: " << m_experiencePoints << " / " << m_experiencePointsLimit << '\n';

    return *this;
}
EntityClass& EntityClass::displayInventory()
{
    std::cout << "Current health is " << m_currentHP << ".\n";
    std::cout << "Current weight is " << m_currentWeight << ".\n";
    std::cout << "Gold is " << m_gold << ".\n";
    
    std::cout << "Inventory: \n";
    for(auto& i : m_inventory)
    {
        std::cout << '\t' << i->getName() << '\n';
    }

    return *this;
}
EntityClass& EntityClass::displayItemInfo()
{
    for(auto& i : m_inventory)
    {
        std::cout << i->getItemID() << ": " << i->getName() << '\n'; 
    }
    
        std::cout << "Which item do you want information on? Enter the item's ID\n\n>";

        int input{ getValidInput<int>() };

        auto itemFound{ std::find_if( m_inventory.begin(), m_inventory.end(), 
        [ input ](EntityClass::item_ptr& item) -> bool 
        { return item->getItemID() == input; } ) };

        if ( itemFound == m_inventory.end() )
        {
            std::cout << "Sorry, that ID is not present in your inventory\n";
        }
        else
        {
            itemFound->get()->itemStats();
        }


    return *this;
}
EntityClass& EntityClass::displayEquipment()
{
    std::cout << "Equipment: \n";

    for(auto& i : m_equipment)
    {
        if(i.second != nullptr)
        {
            std::cout << '\t' << i.second->getName() << '\n';
        }
    }

    return *this;
}
EntityClass& EntityClass::displayEquipmentInfo()
{
    for(auto& i : m_equipment)
    {
        if(i.second != nullptr)
        {
            std::cout << i.second->getItemID() << ": " << i.second->getName() << '\n';
        }
    }

    std::cout << "Which item do you want information on? Enter the item's ID\n\n>";

    int input{ getValidInput<int>() };

    auto itemFound{ std::find_if( m_equipment.begin(), m_equipment.end(), 
        [ input ](std::pair<Item_::item_t, EntityClass::item_ptr>& item) -> bool 
        { 
            if( item.second == nullptr )
            {
            return false;
            }
            return item.second->getItemID() == input; 
            } ) };

    if ( itemFound == m_equipment.end() )
        {
            std::cout << "Sorry, that ID is not present in your inventory\n";
        }
        else
        {
            itemFound->second->itemStats();
        }

    return *this;
}

// Inventory Management
EntityClass& EntityClass::buyOrTakeItem(Item* item, int reduction)
{
    EntityClass::item_ptr inventory_item{ item };

    if(reduction <= m_gold)
    {
        m_gold -= reduction;
    }
    else
    {
        std::cout << "You do not have enough gold\n";
        return *this;
    }

    if( ( m_currentWeight + item->getWeight() ) > m_weightStat )
    {
        std::cout << "This item would go over your weight limit\n";
        return *this;
    }

    
    m_inventory.push_back(inventory_item);
    m_currentWeight += item->getWeight();

    std::cout << "You picked up " << item->getName() << '\n';

    return *this;
}
EntityClass& EntityClass::dropItem()
{
    for(auto& i : m_inventory)
    {
        std::cout << i->getItemID() << ": " << i->getName() << '\n'; 
    }
    
    std::cout << "Which item do you want to drop? Enter the item's ID\n\n>";

    int input{ getValidInput<int>() };

    auto itemFound{ std::find_if( m_inventory.begin(), m_inventory.end(), 
                    [ input ](EntityClass::item_ptr& item) -> bool 
                    { return item->getItemID() == input; } ) };

    if( itemFound != m_inventory.end() )
    {
        std::cout << "Are you sure you want to drop the item? " <<
            "You will never get it back again. (Y)es or (N)o \n\n";
        
        while(true)
        {
            char desition{ getValidInput<char>() };

            switch (desition)
            {
            case 'Y':
            case 'y':
                std::cout << "You dropped " << itemFound->get()->getName() << '\n';
                m_currentWeight -= itemFound->get()->getWeight();
                m_inventory.erase(itemFound);
                return *this;
            case 'N':
            case 'n':
                return *this;

            default:
                std::cout << "Please enter Y or y for Yes or N or n for no\n";
                break;
            }
        }
    }
    else
    {
        std::cout << "Item not found. Please enter correct ID\n";
    }

    return *this;
}

// Equipment Management
EntityClass& EntityClass::equipItem()
{

    if( !m_inventory.empty() )
    {
    for(auto& i : m_inventory)
    {
        std::cout << i->getItemID() << ": " << i->getName() << '\n'; 
    }
    
    std::cout << "Which item do you want to equip? Enter the item's ID\n\n>";

    int input{ getValidInput<int>() };

    auto itemFound{ std::find_if( m_inventory.begin(), m_inventory.end(), 
                    [ input ](EntityClass::item_ptr& item) -> bool 
                    { return item->getItemID() == input; } ) };

    if ( itemFound == m_inventory.end() )
    {
        std::cout << "Sorry, that ID is not present in your inventory\n";
    }
    else
    {
        auto equipCheck{ std::find_if( m_equipment.begin(), m_equipment.end(), 
        [ itemFound ]( std::pair<Item_::item_t, EntityClass::item_ptr>& pair ) 
        -> bool { 
            return (pair.first & itemFound->get()->getItemFlag()).any(); 
        } ) };

        if(equipCheck != m_equipment.end() && equipCheck->second == nullptr )
        {
            equipCheck->second = std::move( *itemFound );
            m_inventory.erase(itemFound);
        }
        else
        {
            std::cout << "Inventory slot full. Try unequiping item.\n";
        }
    }
    }
    else
    {
        std::cout << "Inventory Empty\n";
    }

    return *this;
}
EntityClass& EntityClass::unequipItem()
{
    for(auto& i : m_equipment)
    {
        if(i.second != nullptr)
        {
            std::cout << i.second->getItemID() << ": " << i.second->getName() << '\n';
        }
    }

    std::cout << "Which item do you want to unequip? Enter the item's ID\n\n>";

    int input{ getValidInput<int>() };

    auto itemFound{ std::find_if( m_equipment.begin(), m_equipment.end(), 
        [ input ]( const std::pair<Item_::item_t, EntityClass::item_ptr>& item ) -> bool 
        { 
        if( item.second == nullptr )
        {
            return false;
        }
        
        return item.second->getItemID() == input;

        } ) };

    if ( itemFound != m_equipment.end() )
    {
        std::cout << itemFound->second->getName() << " has been unequiped\n";
        m_inventory.push_back( std::move(itemFound->second) );
        itemFound->second = nullptr;
    }
    else
    {
        std::cout << "Item not found. Please enter correct id.\np";
    }

    return *this;
}

// Level Up
EntityClass& EntityClass::levelUp()
{
    m_experiencePoints -= m_experiencePointsLimit;
    m_experiencePointsLimit *= 1.125;
    m_level += 1;

    int allocationPoints{ 50 };

    while (allocationPoints > 0)
    {
        displayStats();

        std::cout << "Please allocate points to your stats. You have " << 
                    allocationPoints << " left.\n\n>";

        char input{ getValidInput<char>() };
        int* increase{ nullptr };

        switch (input)
        {
        case 'H':
        case 'h':
            increase = &m_hitPointStats;
            break;
        
        case 'D':
        case 'd':
            increase = &m_defence;
            break;
        
        case 'A':
        case 'a':
            increase = &m_attack;
            break;

        case 'Q':
        case 'q':
            increase = &m_quickness;
            break;

        case 'W':
        case 'w':
            increase = &m_weightStat;
            break;

        default:
            std::cout << "You have not entered the correct character to increase a stat. Please do so\n\n";
            continue;
        }

        std::cout << "Please type how many points you wish to allocate in this stat\n\n>";
        int allocatedPoint{ getValidInput<int>() };
        if( allocatedPoint <= allocationPoints )
        {
            *increase += allocatedPoint;
            allocationPoints -= allocatedPoint;
        }
        else
        {
            std::cout << "Please enter an ammount less than or equal to your point limit\n\n";
        }
    }
    
    return *this;
}
bool EntityClass::ifLeveledUp()
{
    return m_experiencePoints > m_experiencePointsLimit;
}

// Combat
int EntityClass::attack()
{
    int attackPower{ m_attack };

    if ( m_equipment[Item_::swordIndex].second )
    {
        attackPower += m_equipment[ Item_::swordIndex ].second->getScalar();
    }

    return attackPower;
}
EntityClass& EntityClass::takeDamage(int damage)
{
    damage -= m_defence;

    if( m_equipment[Item_::armorIndex].second )
    {
        damage -= m_equipment[Item_::armorIndex].second->getScalar();
    }

    if( damage <= 0 )
    {
        damage = 0;
    }

    m_currentHP -= damage;

    return *this;
}
int EntityClass::speed()
{
    int speed{ m_quickness };

    if ( m_equipment[Item_::necklaceIndex].second )
    {
        speed += m_equipment[ Item_::necklaceIndex ].second->getScalar();
    }

    return speed;
}

// Rest
EntityClass& EntityClass::rest()
{
    m_currentHP = m_hitPointStats;

    return *this;
}

// Increase Gold
EntityClass& EntityClass::increaseGold( int increase )
{
    m_gold += increase;

    return *this;
}

// Check Dead
bool EntityClass::checkDead()
{
    return m_currentHP <= 0;
}

// Increase Experience
EntityClass& EntityClass::increaseExperience( int increase )
{
    m_experiencePoints += increase;

    return *this;
}