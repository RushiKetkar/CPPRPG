#include "gameplay.hpp"

bool gameplay( const std::unique_ptr<Player>& player )
{
    std::cout << "Please chose what you want to do: \n";
    std::cout << "> Fight Monster(F)\n";
    std::cout << "> Save Progress(S)\n";
    std::cout << "> Buy items(B)\n";
    std::cout << "> Fight the Final Boss(L)\n";
    std::cout << "> Rest(R)\n";
    std::cout << "> Manage Items(M)\n";
    std::cout << "> Quit Game(Q)\n";
    std::cout << "\n> ";

    char choice{ getValidInput<char>() };

    switch (choice)
    {
    case 'f':
    case 'F':
        return fight( player );
        break;
    
    case 's':
    case 'S':
        std::cout << player->getName() << " is saved\n";
        player->saveCharacter();
        break;

    case 'b':
    case 'B':
        buyOrSell( player );
        break;
    
    case 'l':
    case 'L':
        return fightFinalBoss( player );
        break;
    
    case 'r':
    case 'R':
        rest( player );
        break;
    
    case 'm':
    case 'M':
        manageEquipment( player );
        break;

    case 'q':
    case 'Q':
        return quit();
        break;

    default:
        std::cout << "Please choose valid characters\n";
        break;
    }

    return true;
}

bool fight( const std::unique_ptr<Player>& player )
{
    Monster monster{ getRandomMonster() };

    std::cout << "You encountered a monster!\nIts stats are...\n";
    monster
        .displayStats()
        .displayEquipment();

    while (true)
    {
        std::cout << "Would you like to: \n";
        std::cout << "Fight(F)\n";
        std::cout << "Run(R)\n\n>";

        char input{ getValidInput<char>() };

        switch (input)
        {
            case 'f':
            case 'F':
                {
                if( player->speed() > monster.speed() )
                {
                    std::cout << "You take a swing at the monster!\n";
                    monster.takeDamage( player->attack() );
                    std::cout << "Monster is hit for " << player->attack() << " damage!\n";
                    if( monster.checkDead() )
                    {
                        std::cout << "You killed the " << monster.getName() << ". You get " << monster.getGold() << " gold\n";
                        player->increaseGold( monster.getGold() )
                            .increaseExperience( monster.getLevel() * 10 );
                        return true;
                    }
                    std::cout << "Monster swings at you!\n";
                    player->takeDamage( monster.attack() );
                    std::cout << "You are hit for " << monster.attack() << "damage!\n";
                    if( player->checkDead() )
                    {
                        return false;
                    }
                }
                else
                {
                    std::cout << "Monster swings at you!\n";
                    player->takeDamage( monster.attack() );
                    std::cout << "You are hit for " << monster.attack() << "damage!\n";
                    if( player->checkDead() )
                    {
                        std::cout << "The" << monster.getName() << "has killed you.\n";
                        return false;
                    }
                    std::cout << "You take a swing at the monster!\n";
                    monster.takeDamage( player->attack() );
                    std::cout << "Monster is hit for " << player->attack() << "damage!\n";
                    if( monster.checkDead() )
                    {
                        std::cout << "You killed the " << monster.getName() << ". You get " << monster.getGold() << " gold\n";
                        player->increaseGold( monster.getGold() )
                            .increaseExperience( monster.getLevel() * 10 );
                        return true;
                    }
                }

                break;
                }

            case 'r':
            case 'R':
                {
                int chance{ getRandomNumber(0, 100) };

                if(chance > 50)
                {
                    std::cout << "You have escaped!\n";
                    return true;
                }
                else
                {
                    std::cout << "You have been hit for " << monster.attack() << " damage!\n";
                    player->takeDamage( monster.attack() );

                    if(player->checkDead())
                    {
                        std::cout << "You have died\n";
                        return false;
                    } 
                }
                break;
                }
            default:
                std::cout << "Please enter correct character: \'f\' or \'r\'\n";
                break;
        } 
    }
    
}

bool quit()
{
    while (true)
    {
        std::cout << "Are you sure you want to quit? All unsaved progress will be lost. Yes(Y) or No(N)\n\n>";
        char input{ getValidInput<char>() };
        switch (input)
        {
        case 'Y':
        case 'y':
            return false;
            break;
        case 'N':
        case 'n':
            return true;
            break;

        default:
            std::cout << "Please enter correct character\n";
            break;
    }
    }
    
}

void buyOrSell( const std::unique_ptr<Player>& player )
{
    auto item1{ std::make_unique<Item>( getRandomItem() ) };
    auto item2{ std::make_unique<Item>( getRandomItem() ) };
    auto item3{ std::make_unique<Item>( getRandomItem() ) };

    std::cout << "Welcome to the shop. What items do you want? 1, 2, 3, or none(N). Cost is five times the scalar \n\n1. \n";

    item1->itemStats();

    std::cout << "\n 2. \n";

    item2->itemStats();

    std::cout << "\n 3. \n";

    item3->itemStats();

    std::cout << "\n\n >";

    char input{ getValidInput<char>() };
    switch ( input )
    {
    case '1':

        {
        int cost{ item1->getScalar() * 5 };
        player->buyOrTakeItem( item1.release(), cost );
        break;
        }
    
    case '2':

        {
        int cost{ item2->getScalar() * 5 };
        player->buyOrTakeItem( item2.release(), cost );
        break;
        }

    case '3':

        {
        int cost{ item3->getScalar() * 5 };
        player->buyOrTakeItem( item3.release(), cost );
        break;
        }

    case 'n':
    case 'N':
        return;

    default:
        std::cout << "Please type correct characters \'1\', \'2\', \'3\', or n\n";
        break;
    }
    
}

void manageEquipment( const std::unique_ptr<Player>& player )
{
    player
        ->displayInventory()
        .displayEquipment();
    
    bool loop{ true };

    while ( loop )
    {
        std::cout << "What would you like to do? Equip Item(E), Unequip Item(U), Drop Item(D), information on items(I), information on equipment(P), or quit(Q)\n\n> ";

        char input{ getValidInput<char>() };

        switch (input)
        {
        case 'E':
        case 'e':
            player->equipItem();
            break;

        case 'U':
        case 'u':
            player->unequipItem();
            break;
        
        case 'D':
        case 'd':
            player->dropItem();
            break;

        case 'I':
        case 'i':
            player->displayItemInfo();
            break;

        case 'P':
        case 'p':
            player->displayEquipmentInfo();
            break;

        case 'q':
        case 'Q':
            loop = false;
            break;

        default:
            std::cout << "Please enter correct characters\n";
            break;
        }
    }
    

}

bool fightFinalBoss( const std::unique_ptr<Player>& player )
{
    Monster monster{ Monster::FinalBoss };

    std::cout << "You encountered the final boss!\nIts stats are...\n";
    monster
        .displayStats()
        .displayEquipment();

    while (true)
    {
        std::cout << "Would you like to: \n";
        std::cout << "Fight(F)\n";
        std::cout << "Run(R)\n\n>";

        char input{ getValidInput<char>() };

        switch (input)
        {
            case 'f':
            case 'F':

                {
                if( player->speed() > monster.speed() )
                {
                    std::cout << "You take a swing at the final boss!\n";
                    monster.takeDamage( player->attack() );
                    std::cout << "The final boss is hit for " << player->attack() << " damage!\n";
                    if( monster.checkDead() )
                    {
                        std::cout << "You killed the " << monster.getName() << ". You get " << monster.getGold() << " gold\n";
                        std::cout << "You have won the game. Congrats!\n";
                        player->increaseGold( monster.getGold() )
                            .increaseExperience( monster.getLevel() * 10 );
                        return false;
                    }
                    std::cout << "The final boss swings at you!\n";
                    player->takeDamage( monster.attack() );
                    std::cout << "You are hit for " << monster.attack() << " damage!\n";
                    if( player->checkDead() )
                    {
                        
                        return false;
                    }
                }
                else
                {
                    std::cout << "The final boss swings at you!\n";
                    player->takeDamage( monster.attack() );
                    std::cout << "You are hit for " << monster.attack() << "damage!\n";
                    if( player->checkDead() )
                    {
                        std::cout << "The" << monster.getName() << "has killed you.\n";
                        return false;
                    }
                    std::cout << "You take a swing at the monster!\n";
                    monster.takeDamage( player->attack() );
                    std::cout << "The final boss is hit for " << player->attack() << "damage!\n";
                    if( monster.checkDead() )
                    {
                        std::cout << "You killed the " << monster.getName() << ". You get " << monster.getGold() << " gold\n";
                        std::cout << "You have won the game. Congrats!\n";
                        player->increaseGold( monster.getGold() )
                            .increaseExperience( monster.getLevel() * 10 );
                        return true;
                    }
                }

                break;
                }

            case 'r':
            case 'R':

                {
                int chance{ getRandomNumber(0, 100) };

                if(chance > 50)
                {
                    std::cout << "You have escaped!\n";
                    return true;
                }
                else
                {
                    std::cout << "You have been hit for " << monster.attack() << " damage!\n";
                    player->takeDamage( monster.attack() );

                    if(player->checkDead())
                    {
                        std::cout << "You have died\n";
                        return false;
                    } 
                }

                break;
                }

            default:
                std::cout << "Please enter correct character: \'f\' or \'r\'\n";
                break;
        } 
    }
    
}

void rest( const std::unique_ptr<Player>& player )
{
    std::cout << "You rest for the night.\n";
    player->rest()
        .displayStats();
    
    if( player->ifLeveledUp() )
    {
        player->levelUp();
    }

}

std::unique_ptr<Player> createOrLoadPlayer()
{
    bool isCreatedCharacter{ true };

    while (true)
    {
        std::cout << "Do you want to create a new character(N) or load previous character(P)?\n\n> ";

        char input{ getValidInput<char>() };

        switch (input)
        {
        case 'n':
        case 'H':
            {
                auto newCharacter{ std::make_unique<Player>() };
                return std::move( newCharacter );
            }
        
        case 'P':
        case 'p':
            {
                std::cout << "Please enter file name\n\n> ";

                std::string fileName;

                std::getline( std::cin >> std::ws, fileName );

                std::ifstream characterFile{ fileName };

                if( characterFile )
                {
                    auto loadCharacter{ std::make_unique<Player>( fileName ) };
                    return std::move( loadCharacter );
                }
                else
                {
                    std::cout << "File could not be loaded\n";
                }
            }

        default:
            break;
        }
    }
    
}