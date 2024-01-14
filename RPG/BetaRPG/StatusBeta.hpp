#ifndef STATUS_GUARD
#define STATUS_GUARD

#include <bitset>

namespace StatusFlags
{
    using status_t = std::bitset<16>;
    
    inline constexpr status_t poison{ 1 };
    inline constexpr status_t weakness{ 1 << 1 };
    inline constexpr status_t sluggish{ 1 << 2 };
    inline constexpr status_t confusion{ 1 << 3 };
    inline constexpr status_t strength{ 1 << 4 };
    inline constexpr status_t speed{ 1 << 5 };
    inline constexpr status_t sharpness{ 1 << 6 };
    inline constexpr status_t tough{ 1 << 7 };
    inline constexpr status_t brittle{ 1 << 8 };
}


class Status
{
private:
    int m_scalar;     
    StatusFlags::status_t m_statusFlag;
    bool m_relateToItem;
    int m_counter;
    int m_statusID;
    static int m_IDGen;
public:
    Status(StatusFlags::status_t statusFlag = 0, int counter = 5, int scalar = 1);
    ~Status();

    bool getrelateToItem();
    int getID();
    int getScalar();
    int getCounter();
    const StatusFlags::status_t& getStatus();
    Status& reduceCounter();
};

#endif