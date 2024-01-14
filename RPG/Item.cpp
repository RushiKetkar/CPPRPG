#include "Item.hpp"

Item::Item(int itemIndex, std::string name,
int scalar, int weight ) : m_scalar{ scalar }, 
m_weight{ weight }, m_itemFlag{ Item_::flagArray[ itemIndex ] }, 
m_name{ name }, m_itemID{ m_IDGen }
{ 
    m_IDGen++;
}

Item::Item(std::string name, 
Item_::item_t itemFlag, 
int scalar, int weight) : m_name{ name },
m_itemFlag{ itemFlag }, m_itemID{ m_IDGen },
m_scalar{ scalar }, m_weight{ weight }
{
    m_IDGen++;
}

Item::~Item() { }

int Item::m_IDGen { 0 };

const Item_::item_t& Item::getItemFlag() const { return m_itemFlag; }
int Item::getScalar() const { return m_scalar; }
int Item::getWeight() const { return m_weight; }
int Item::getItemID() const { return m_itemID; }
const std::string_view Item::getName() const { return m_name; }

Item& Item::itemStats()
{
    std::cout << "Item name is " << m_name << ".\n";
    std::cout << "Item addition is " << m_scalar << ".\n";
    std::cout << "Item weight is " << m_weight << ".\n";

    return *this;
}

Item getRandomItem()
{
    int index{ getRandomNumber(0, 2) };

    return Item{ index, static_cast<std::string>(itemNames[ index ]), getRandomNumber(10, 70), getRandomNumber( 30, 100) };
}