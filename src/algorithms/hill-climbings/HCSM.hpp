#ifndef __HCSM__
#define __HCSM__

#include "../../cube/CUBE.hpp"
#include "../../functions/objective-function/OBJECTIVE-FUNCTION.hpp"

class HCSM
{
private:
    CUBE cube;
    OBJECTIVE_FUNCTION obj_func;

    int MAX_SIDEWAYS;

    pair<int, int> FIND_BEST();

public:
    HCSM(CUBE cube, int opt = 0, int max_sideways = 100);

    void SET_CUBE(CUBE cube);
    void SET_OPTION(int opt = 0);
    void RUN();
};

#endif