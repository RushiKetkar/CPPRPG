#include "Player.hpp"


Player::Player(const std::string& fileName) : EntityClass{ }
{
    m_equipment[0].second = nullptr;
    m_equipment[1].second = nullptr;
    m_equipment[2].second = nullptr;

    std::ifstream saveFile{ fileName };

    std::string name;
    int hitPointStats;
    int currentHP;
    int level;
    double experiencePoints;
    double experiencePointsLimit;
    int attack;
    int defence;
    int quickness;
    int weightStat;
    int currentWeight;
    int gold;

    std::getline( saveFile, name );

    saveFile >> currentHP >> currentWeight >> 
    experiencePoints >> experiencePointsLimit >> level
    >> hitPointStats >> attack >> defence >> quickness
    >> weightStat >> gold;

    m_name = name;
    m_currentHP = currentHP;
    m_currentWeight = currentWeight;
    m_experiencePoints = experiencePoints;
    m_experiencePointsLimit = experiencePointsLimit;
    m_level = level;
    m_hitPointStats = hitPointStats;
    m_attack = attack;
    m_defence = defence;
    m_quickness = quickness;
    m_weightStat = weightStat;
    m_gold = gold;
    
    while(true)
    {
        std::string endOrName;

        saveFile >> endOrName;

        if( endOrName.compare( "end" ) != 0 )
        {
            std::string restOfName;
            std::getline( saveFile, restOfName );
            endOrName.append( restOfName );

            int scalar;
            int weight;
            std::size_t itemFlag;

            saveFile >> scalar >> weight >> itemFlag;

            auto item { std::make_shared<Item>( endOrName, static_cast<Item_::item_t>(itemFlag), scalar, weight ) };

            int index;
            
            if( ( item->getItemFlag() & Item_::swordFlag ).any() )
            {
                index = Item_::swordIndex;
            }
            if( ( item->getItemFlag() & Item_::armorFlag ).any() )
            {
                index = Item_::armorIndex;
            }
            if( ( item->getItemFlag() & Item_::necklaceFlag ).any() )
            {
                index = Item_::necklaceIndex;
            }

            m_equipment.at( index ).second = std::move( item ); 

        }
        else
        {
            break;
        }
    }

    while (true)
    {
        std::string endOrName;

        saveFile >> endOrName;

        if( endOrName.compare( "end" ) != 0 )
        {
            std::string restOfName;
            std::getline( saveFile, restOfName );
            endOrName.append( restOfName );

            int scalar;
            int weight;
            std::size_t itemFlag;

            saveFile >> scalar >> weight >> itemFlag;

            auto item { std::make_shared<Item>( endOrName, scalar, weight, itemFlag ) };

            m_inventory.push_back( std::move( item ) );
        }
        else
        {
            break;
        }
    }
    
}

Player::Player() : EntityClass{ "", 10, 1, 1, 1, 1, 10, 0 }
{
    m_currentWeight = 0;

    std::cout << "Welcome! The first step to create your character is to give them a name. ";

    bool loopBreak{ true };
    while( loopBreak )
    {
        std::cout << "What the name of your character: ";

        std::getline(std::cin >> std::ws, m_name);

        std::cout << "Are you sure you want to go by this name? Yes(Y) or No(N)\n\n>";
        char yesOrNo{ getValidInput<char>() };
        
        switch (yesOrNo)
        {
        case 'y':
        case 'Y':
            loopBreak = false;
            break;
        case 'N':
        case 'n':
            continue;
        default:
            std::cout << "Please enter Y for Yes or N for No\n";
            break;
        }
    }

    int points{ 100 };

    std::cout << "You have 5 stats: Hitpoints(H), Attack(A)," <<
    " Defence(D), Quickness(Q), and Weight(W).\n";

    bool pointLoopBreak { true };
    while( pointLoopBreak )
    {
        std::cout << "You have " << points << " points to spend. " <<
        "Please choose which stat to allocate points to:\n\n>";

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
        if( allocatedPoint <= points )
        {
            *increase += allocatedPoint;
            points -= allocatedPoint;
        }
        else
        {
            std::cout << "Please enter an ammount less than or equal to your point limit\n\n";
        }

        if( points <= 0 )
        {
            std::cout << "Are you happy with this stat spread? Yes(Y) or No(N)\n";
            displayStats();
            std::cout << '>';
            bool loopBreak{ true };
            while( loopBreak )
            {
                char yesOrNo{ getValidInput<char>() };
        
                switch (yesOrNo)
                {
                    case 'y':
                    case 'Y':
                        loopBreak = false;
                        pointLoopBreak = false;
                        m_currentHP = m_hitPointStats;
                        break;
                    break;
                    case 'N':
                    case 'n':
                        points = 70;
                        m_hitPointStats = 0;
                        m_attack = 0;
                        m_defence = 0;
                        m_quickness = 0;
                        m_weightStat = 0;
                        loopBreak = false;
                        break;
                    default:
                        std::cout << "Please enter Y for Yes or N for No\n";
                        break;
                }
            }
        }
    }
}

Player& Player::saveCharacter()
{
    std::string textFileName{ getName() };

    textFileName.append( ".txt" );

    std::ofstream saveFile{ textFileName };

    if(!saveFile)
    {
        std::cerr << "Save file error\n";
        return *this;
    }

    saveFile << m_name << "\n "
    << m_currentHP << ' '
    << m_currentWeight << ' '
    << m_experiencePoints << ' '
    << m_experiencePointsLimit << ' '
    << m_level << ' '
    << m_hitPointStats << ' '
    << m_attack << ' '
    << m_defence << ' '
    << m_quickness << ' '
    << m_weightStat << ' '
    << m_gold << "\n";

    for(int i{ 0 }; i < 3; ++i)
    {
        if(m_equipment[i].second != nullptr)
        {
            saveFile << m_equipment[i].second->getName() <<
            '\n' << ' ' << m_equipment[i].second->getScalar()
            << ' ' << m_equipment[i].second->getWeight() << ' ' <<
            m_equipment[i].second->getItemFlag() << '\n';
        }
    }

    saveFile << "end\n";

    if( !m_inventory.empty() )
    {
        for( auto& i : m_inventory )
        {
            saveFile << i->getName() << '\n' << 
            ' ' << i->getScalar()
            << ' ' << i->getWeight() << ' ' <<
            i->getItemFlag() << ' ' << '\n';
        }

        saveFile << "end\n";

    }

    return *this;
}

