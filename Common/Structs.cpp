#include "Structs.h"

namespace std
{
    namespace Random
    {
        static std::mt19937 gen(time(nullptr));
        double randomDouble(double i_left, double i_right)
        {
            std::uniform_real_distribution<> dis(i_left, i_right);
            return dis(gen);
        }
        int randomInt(int i_left, int i_right)
        {
            std::uniform_int_distribution<> dis(i_left, i_right);
            return dis(gen);
        }
    }
}