#include "EntityBase.hpp"

EntityClass::EntityClass(std::string name, int hitPoints,
int level, int attack, int defence, int quickness, 
int weight, int magicAffinity, 
ItemFlags::item_t itemFlags, int currentWeight,
int gold) : 
m_attack{ attack }, 
m_defence{ defence }, m_hitPoints{ hitPoints }, 
m_level{ level }, m_magicAffinity{ magicAffinity },
m_quickness{ quickness }, m_weight{ weight },
m_itemFlags{ itemFlags }, m_name{ name }, 
m_currentWeight{ currentWeight },
m_gold{ gold } {  }

EntityClass::~EntityClass() {}

int EntityClass::getHitpoints() { return m_hitPoints; }
int EntityClass::getDefence() { return m_defence; }
int EntityClass::getAttack() { return m_attack; }
int EntityClass::getLevel() { return m_level; }
int EntityClass::getMagicAffinity() { return m_magicAffinity; }
int EntityClass::getQuickness() { return m_quickness; }
int EntityClass::getWeight() { return m_weight; }
int EntityClass::getGold() { return m_gold; }

EntityClass& EntityClass::examine()
{
    std::cout << "Name(N): " << m_name << '\n';
    std::cout << "Health(H): " << m_hitPoints << '\n';
    std::cout << "Defence(D): " << m_defence << '\n';
    std::cout << "Attack Power(A): " << m_attack << '\n';
    std::cout << "Level(L): " << m_level << '\n';
    std::cout << "Magic Affinity(M): " << m_magicAffinity << '\n';
    std::cout << "Quickness(Q): " << m_quickness << '\n';
    std::cout << "Weight(W): " << m_weight << '\n';

    return *this;
}

EntityClass& EntityClass::heal(int increase)
{ 
    m_hitPoints += increase;
    return *this; 
}
EntityClass& EntityClass::cureStatus(const StatusConstants::status_t& type)
{
    for(auto i{ m_statusList.begin() }; i != m_statusList.end(); ++i)
    {
        if( (i->second->getStatus() & type).any() )
        {
            i->second.release();
            i->second = nullptr;
            m_statusList.erase(i);
            break;
        }
    }

    return *this;
}

EntityClass& EntityClass::inflictStatus(EntityClass::status_ptr& status)        // has a bug in which if the same status is inflicted, the game crashes
{
    m_statusList.insert( {status->getID(), std::move(status)} );
    status = nullptr;
    return *this;
}

bool EntityClass::checkDead() 
{
    statusReduce();

    return ( (m_hitPoints <= 0) ? true : false ); 
}

EntityClass& EntityClass::statusReduce()
{
    if(m_statusList.empty())
    {
        return *this;
    }

    for(auto i{ m_statusList.begin() }; i != m_statusList.end(); ++i)
    {
        if( i->second->getrelateToItem() ) 
        {
            continue;
        }

        if( i->second->getCounter() <= 0 )
        {  
            i->second;
            i->second = nullptr;
            m_statusList.erase(i);
        }
    }

    return *this;
}

EntityClass& EntityClass::levelUp()
{
    ++m_level;
    int point{ 10 };
    std::cout << "Choose where to allocate points: \n";
    char decision{};
    int pointAllocation{};

    do
    {
        examine();
        std::cout << "\nYou have " << point << " points to spend\n";
        std::cout << "Please choose which stat to increase.\n";
        std::cout << "Increasable stats are: \n";
        std::cout << "Attack: A\n";
        std::cout << "Quickness: Q\n";
        std::cout << "Defence: D\n";
        std::cout << "Weight: W\n";
        std::cout << "Hitpoints: H\n";
        std::cout << "Magic Affinity: M\n"; 
        while(true)
        {
            std::cout << "\n>";
            try
            {
                decision = getValidInput<char>();
                switch (decision)
                {
                case 'A':
                case 'Q':
                case 'D':
                case 'W':
                case 'H':
                case 'M':
                case 'a':
                case 'q':
                case 'd':
                case 'w':
                case 'h':
                case 'm':
                    break;
                default:
                    std::cout << "\nPlease choose right symbols for stats.\n";
                    continue;
                }
            }
            catch(const std::exception& e)
            {
                std::cout << "\nPlease do not enter extraneous characters.\n";
                continue;
            }

            break;
        }

        std::cout << "\nHow many points would you like to put in this?\n";

        while (true)
        {
            std::cout << "\n>";

            try
            {
                pointAllocation = getValidInput<int>();

                if(pointAllocation > point)
                {
                    std::cout << "\nPlease choose numbers under " << point << '\n';
                    continue; 
                }
            }
            catch(const std::exception& e)
            {
                std::cout << "\nPlease do not enter anything aside from a number\n";
                continue;
            }
            
            point -= pointAllocation;

            break;
        }
        

        
    } while (point != 0);
    
    return *this;
}

int EntityClass::attack()
{
    int attackPower{ m_attack };

    for (auto i{ m_statusList.begin() }; i != m_statusList.end(); ++i)
    {
        if( (i->second->getStatus() & StatusConstants::weakness).any() )
        {
            int statusDecrease{ (i->second->getScalar() - (m_magicAffinity)) };

            if(statusDecrease >= 0)
            {
                attackPower -= statusDecrease;
            }
        }

        if( (i->second->getStatus() & StatusConstants::strength).any() )
        {
            int statusIncrease{ (i->second->getScalar() + (m_magicAffinity)) };

            if(statusIncrease >= 0)
            {
                attackPower += statusIncrease;
            }
        }
    }
    
    return attackPower;
}
EntityClass& EntityClass::takeDamage(int damage)
{
    int damageTotal{ damage };

    damageTotal -= m_defence;

    for (auto i{ m_statusList.begin() }; i != m_statusList.end(); ++i)
    {
        if( (i->second->getStatus() & StatusConstants::brittle).any() )
        {
            int statusIncrease{ (i->second->getScalar() - (m_magicAffinity)) };

            if(statusIncrease >= 0)
            {
                damageTotal += statusIncrease;
            }
        }

        if( (i->second->getStatus() & StatusConstants::tough).any() )
        {
            int statusDecrease{ (i->second->getScalar() + (m_magicAffinity)) };

            if(statusDecrease >= 0)
            {
                damageTotal -= statusDecrease;
            }
        }
    }

    if(damageTotal > 0)
    {
        m_hitPoints -= damageTotal;
    }

    return *this;
}

EntityClass& EntityClass::checkStatus()
{
    using namespace StatusConstants;

    std::cout << "Statuses Inflicted: \n";

    for(auto i{ m_statusList.begin() }; i != m_statusList.end(); ++i)
    {
        std::cout << '\t';

        if( (i->second->getStatus() & brittle).any() )
        {
            std::cout << "Brittle. Strength of Status = " << i->second->getScalar() << '\n';
        }

        if( (i->second->getStatus() & weakness).any() )
        {
            std::cout << "Weakness. Strength of Status = " << i->second->getScalar() << '\n';
        }

        if( (i->second->getStatus() & poison).any() )
        {
            std::cout << "Poison. Strength of Status = " << i->second->getScalar()  << '\n';
        }

        if( (i->second->getStatus() & sluggish).any() )
        {
            std::cout << "Sluggish. Strength of Status = " << i->second->getScalar() << '\n';
        }

        if( (i->second->getStatus() & sharpness).any() )
        {
            std::cout << "Sharpness. Strength of Status = " << i->second->getScalar() << '\n';
        }

        if( (i->second->getStatus() & tough).any() )
        {
            std::cout << "Tough. Strength of Status = " << i->second->getScalar() << '\n';
        }

        if( (i->second->getStatus() & confusion).any() )
        {
            std::cout << "Confusion. Strength of Status = " << i->second->getScalar() << '\n';
        }

        if( (i->second->getStatus() & strength).any() )
        {
            std::cout << "Strength. Strength of Status = " << i->second->getScalar() << '\n';
        }

        if( (i->second->getStatus() & speed).any() )
        {
            std::cout << "Speed. Strength of Status = " << i->second->getScalar() << '\n';
        }
    }

    return *this;
}

EntityClass& EntityClass::increaseGold(int increase)
{
    m_gold += increase;
    return *this;
}

EntityClass& EntityClass::buyItem(EntityClass::item_ptr& item, int reduction)
{
    if(reduction < m_gold)
    {
        m_gold -= reduction;

    }
    else
    {
        std::cout << "You do not have enough to buy that item";
    }
    

    return *this;
}