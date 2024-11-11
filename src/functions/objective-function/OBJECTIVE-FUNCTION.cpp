#include "OBJECTIVE-FUNCTION.hpp"

#include <numeric>

using namespace std;

int OBJECTIVE_FUNCTION::OPTION_0(CUBE cube)
{
    int res = 0;
    for (int i = 0; i < 109; i++)
        res += abs(315 - accumulate(cube.constraints[i].begin(),
                                    cube.constraints[i].end(),
                                    0));
    return res;
}

int OBJECTIVE_FUNCTION::OPTION_1(CUBE cube)
{
    return 0;
}

int OBJECTIVE_FUNCTION::OPTION_2(CUBE cube)
{
    return 0;
}

OBJECTIVE_FUNCTION::OBJECTIVE_FUNCTION(int opt) { this->option = opt; }

void OBJECTIVE_FUNCTION::SET_OPTION(int opt) { this->option = opt; }

int OBJECTIVE_FUNCTION::CALCULATE(CUBE cube)
{
    if (this->option == 1)
        return OPTION_1(cube);
    else if (this->option == 2)
        return OPTION_2(cube);
    else
        return OPTION_0(cube);
}
