#ifndef VALIDINPUT_GUARD
#define VALIDINPUT_GUARD


void ignoreLine();          // ignores character in the std::cin buffer

template<typename T>        // Gets safe input
T getValidInput()
{
    while (true)
    {
        T input;
        std::cin >> input;

        if(!std::cin)
        {
            std::cin.clear();
            ignoreLine();
            std::cout << "Please enter a valid input\n\n>";
        }
        else
        {
            //std::cout << "Valid Input success";
            ignoreLine();
            return input;
        }
    }
    
}

#endif