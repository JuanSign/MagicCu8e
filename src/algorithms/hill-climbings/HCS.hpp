#ifndef __HCS__
#define __HCS__

#include "../../cube/CUBE.hpp"
#include "../../functions/objective-function/OBJECTIVE-FUNCTION.hpp"

class HCS
{
private:
    CUBE cube;
    OBJECTIVE_FUNCTION obj_func;

    int NMAX;

    tuple<int, int, int> GENERATE_SWAP();

public:
    HCS(CUBE cube, int opt = 0, int NMAX = 500);

    void SET_CUBE(CUBE cube);
    void SET_OPTION(int opt = 0);
    void RUN();
};

#endif