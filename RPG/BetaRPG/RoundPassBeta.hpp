#ifndef ROUNDPASS_GUARD
#define ROUNDPASS_GUARD

class RoundPass
{
private:
    bool m_roundPassed;
public:
    RoundPass();

    bool checkPassed();
    void roundPassed();
    void roundStart();
};

extern RoundPass g_round;

#endif