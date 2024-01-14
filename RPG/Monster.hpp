#ifndef MONSTER_GUARD
#define MONSTER_GUARD

#include "EntityBase.hpp"
#include "randomNumber.hpp"

class Monster;

inline constexpr std::array<std::string_view, 7> monsterNames
{ "Goblin", "Orc", "Slime", "Minotaur", "Ghost", "Dragon", "Dusken the Destroyer" };

class Monster : public EntityClass
{
public:
    enum MonsterType
    {
        Goblin,
        Orc,
        Slime,
        Minotaur,
        Ghost,
        Dragon,
        FinalBoss,

        endMonsterType
    };
protected:
    MonsterType m_type;
public:
    Monster( MonsterType type = Goblin );
    ~Monster();

    EntityClass& increaseExperience() = delete;
    EntityClass& rest() = delete;
    EntityClass& levelUp() = delete;
    EntityClass& increaseGold() = delete;
    EntityClass& displayEquipmentInfo() = delete;
    EntityClass& displayItemInfo() = delete;

};

Monster getRandomMonster();

#endif