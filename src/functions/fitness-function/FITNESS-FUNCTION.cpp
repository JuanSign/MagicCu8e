#include "FITNESS-FUNCTION.hpp"

#include <cmath>
#include <numeric>

int FITNESS_FUNCTION::OPTION_0(CUBE cube)
{
    int res = 0;
    for (int i = 0; i < 109; i++)
        res += abs(315 - accumulate(cube.constraints[i].begin(),
                                    cube.constraints[i].end(),
                                    0));
    return res;
}

int FITNESS_FUNCTION::OPTION_1(CUBE cube)
{
    return 0;
}

int FITNESS_FUNCTION::OPTION_2(CUBE cube)
{
    return 0;
}

FITNESS_FUNCTION::FITNESS_FUNCTION(int opt) { this->option = opt; }

void FITNESS_FUNCTION::SET_OPTION(int opt) { this->option = opt; }

int FITNESS_FUNCTION::CALCULATE(CUBE cube)
{
    switch (option)
    {
    case 1:
        return this->OPTION_1(cube);
        break;
    case 2:
        return this->OPTION_2(cube);
        break;
    default:
        return this->OPTION_0(cube);
        break;
    }
}