#ifndef __HCSA__
#define __HCSA__

#include "../../cube/CUBE.hpp"
#include "../../functions/objective-function/OBJECTIVE-FUNCTION.hpp"

class HCSA
{
private:
    CUBE cube;
    OBJECTIVE_FUNCTION obj_func;

    pair<int, int> FIND_BEST();

public:
    HCSA(CUBE cube, int opt = 0);

    void SET_CUBE(CUBE cube);
    void SET_OPTION(int opt = 0);
    void RUN();
};

#endif