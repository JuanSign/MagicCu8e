#include "FITNESS-FUNCTION.hpp"

int FITNESS_FUNCTION::OPTION_0(CUBE cube, int cross_point)
{
    return 0;
}

int FITNESS_FUNCTION::OPTION_1(CUBE cube, int cross_point)
{
    return 0;
}

int FITNESS_FUNCTION::OPTION_2(CUBE cube, int cross_point)
{
    return 0;
}

FITNESS_FUNCTION::FITNESS_FUNCTION(int opt = 0) { this->option = opt; }

void FITNESS_FUNCTION::SET_OPTION(int opt = 0) { this->option = opt; }

int FITNESS_FUNCTION::CALCULATE(CUBE cube, int cross_point)
{
    switch (option)
    {
    case 1:
        return this->OPTION_1(cube, cross_point);
        break;
    case 2:
        return this->OPTION_2(cube, cross_point);
        break;
    default:
        return this->OPTION_0(cube, cross_point);
        break;
    }
}