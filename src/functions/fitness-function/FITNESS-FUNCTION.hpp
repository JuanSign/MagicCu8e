#ifndef __FIT_FUNC__
#define __FIT_FUNC__

#include "../../cube/CUBE.hpp"

class FITNESS_FUNCTION
{
private:
    int option;

    int OPTION_0(CUBE cube);
    int OPTION_1(CUBE cube);
    int OPTION_2(CUBE cube);

public:
    FITNESS_FUNCTION(int opt = 0);

    void SET_OPTION(int opt = 0);
    int CALCULATE(CUBE cube);
};

#endif