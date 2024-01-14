#include "Monster.hpp"

Monster::Monster( Monster::MonsterType type ) : m_type{ type }, 
EntityClass{ static_cast<std::string>( monsterNames[ static_cast<int>( type ) ] ) }
{
    m_currentWeight = 0;
    m_weightStat = 100;   

    std::array< int* , 7> stats
    { &m_level, &m_hitPointStats, &m_currentHP, &m_attack, &m_defence, &m_quickness, &m_gold}; 

    auto assignStats
    {  
        [ &stats ]( int level ) -> void
        {

            *stats[0] = level;
            *stats[1] = level * getRandomNumber( 5, 10 );
            *stats[2] = *stats[1];
            *stats[3] = level * getRandomNumber( 2, 7 );
            *stats[4] = level * getRandomNumber( 2, 7 );
            *stats[5] = level * getRandomNumber( 2, 7 );
            *stats[6] = level * getRandomNumber( 10, 15 );
        } 
    };

    switch ( type )
    {
    case Monster::Goblin:
        assignStats( getRandomNumber( 1, 5 ) );
        break;
    case Monster::Orc:
        assignStats( getRandomNumber( 3, 7 ) );
        break;
    case Monster::Slime:
        assignStats( getRandomNumber( 9, 11 ) );
        break;
    case Monster::Minotaur:
        assignStats( getRandomNumber( 11, 13 ) );
        break;
    case Monster::Ghost:
        assignStats( getRandomNumber( 13, 15 ) );
        break;
    case Monster::Dragon:
        assignStats( getRandomNumber( 15, 20 ) );
        break;
    case Monster::FinalBoss:
        assignStats( 25 );
        break;
    default:
        break;
    }

    int swordChance{ getRandomNumber( 0, 100 ) };
    int armorChance{ getRandomNumber( 0, 100 ) };
    int necklaceChance{ getRandomNumber( 0, 100 ) };

    if( swordChance < 25 )
    {
        m_equipment[0].second = std::move( std::shared_ptr<Item>
        {
            new Item{ Item_::swordIndex, "Sword", getRandomNumber( 5, 25 ), getRandomNumber( 5, 50 )} 
        } );
    }
    if( armorChance < 25 )
    {
        m_equipment[1].second = std::move( std::shared_ptr<Item>
        {
            new Item{ Item_::armorIndex, "Armor", getRandomNumber( 5, 25 ), getRandomNumber( 5, 50 )} 
        } );
    }
    if( necklaceChance < 25 )
    {
        m_equipment[2].second = std::move( std::shared_ptr<Item>
        {
            new Item{ Item_::necklaceIndex, "Necklace", getRandomNumber( 5, 25 ), getRandomNumber( 5, 50 )} 
        } );
    }
    
}

Monster::~Monster() { }

Monster getRandomMonster()
{
    int seed{ getRandomNumber(0, 100) };
    Monster::MonsterType type;

    if( seed <= 25 )
    {
        type = Monster::Goblin;
    }
    if( 25 < seed && seed <= 50 )
    {
        type = Monster::Orc;
    }
    if( 50 < seed && seed <= 70 )
    {
        type = Monster::Slime;
    }
    if( 70 < seed && seed <= 85 )
    {
        type = Monster::Minotaur;
    }
    if( 85 < seed && seed <= 95 )
    {
        type = Monster::Ghost;
    }
    if( 95 < seed && seed <= 100 )
    {
        type = Monster::Dragon;
    }

    return Monster{ type };
}