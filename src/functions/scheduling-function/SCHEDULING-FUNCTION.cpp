#include "SCHEDULING-FUNCTION.hpp"

#include <cmath>

using namespace std;

double SCHEDULING_FUNCTION::OPTION_0(int iteration)
{
    return this->temperature * pow(this->alpha, iteration);
}

double SCHEDULING_FUNCTION::OPTION_1(int iteration)
{
    return this->temperature - alpha * iteration;
}

double SCHEDULING_FUNCTION::OPTION_2(int iteration)
{
    return this->temperature / (1 + alpha * iteration);
}

double SCHEDULING_FUNCTION::OPTION_3(int iteration)
{
    return this->temperature / (log(alpha + iteration));
}

double SCHEDULING_FUNCTION::OPTION_4(int iteration)
{
    return this->temperature / (1 + iteration);
}

double SCHEDULING_FUNCTION::OPTION_5(int iteration)
{
    return this->temperature / (1 + log(1 + iteration));
}

SCHEDULING_FUNCTION::SCHEDULING_FUNCTION(int opt, double initial_temp)
{
    this->SET_OPTION(opt, initial_temp);
}

void SCHEDULING_FUNCTION::SET_OPTION(int opt, double initial_temp)
{
    this->option = opt;
    this->temperature = initial_temp;

    switch (option)
    {
    case 1:
        this->alpha = 0.1;
        break;
    case 2:
        this->alpha = 0.01;
        break;
    case 3:
        this->alpha = 5;
        break;
    default:
        this->alpha = 0.99;
        break;
    }
}

void SCHEDULING_FUNCTION::SET_ALPHA(double alpha) { this->alpha = alpha; }

double SCHEDULING_FUNCTION::CALCULATE(int iteration)
{
    switch (option)
    {
    case 1:
        return this->OPTION_1(iteration);
        break;
    case 2:
        return this->OPTION_2(iteration);
        break;
    case 3:
        return this->OPTION_3(iteration);
        break;
    case 4:
        return this->OPTION_4(iteration);
        break;
    case 5:
        return this->OPTION_5(iteration);
        break;
    default:
        return this->OPTION_0(iteration);
        break;
    }
}

double SCHEDULING_FUNCTION::GET_INITIAL() { return this->temperature; }
