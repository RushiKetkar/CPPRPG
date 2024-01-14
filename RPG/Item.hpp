#ifndef ITEM_GUARD
#define ITEM_GUARD

#include <bitset>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <iostream>

#include "randomNumber.hpp"

constexpr std::array<std::string_view, 3> itemNames{ "Sword", "Armor", "Necklace" };

namespace Item_                                         // Item Flags
{
    using item_t = std::bitset<8>;

    inline constexpr int swordIndex { 0 };
    inline constexpr int armorIndex { 1 };
    inline constexpr int necklaceIndex { 2 };

    inline constexpr item_t swordFlag{ 1 };
    inline constexpr item_t armorFlag{ 1 << 1 };
    inline constexpr item_t necklaceFlag{ 1 << 2 };

    inline constexpr std::array<item_t, 3> flagArray { swordFlag, armorFlag, necklaceFlag};
}

class Item                                                  // Item Class
{
private:
    int m_scalar;
    int m_weight;
    int m_itemID;                                            // Stores the Item's ID
    static int m_IDGen;                                        // Makes ID for each item
    Item_::item_t m_itemFlag;
    std::string m_name; 

public:
    Item(int itemIndex = 0, std::string name = "", int scalar = 5, int weight = 10);
    Item(std::string name, Item_::item_t itemFlag, int scalar, int weight);
    ~Item();

    int getScalar() const;
    int getWeight() const;
    const Item_::item_t& getItemFlag() const;
    int getItemID() const;
    const std::string_view getName() const;
    
    Item& itemStats();
};

Item getRandomItem();

#endif