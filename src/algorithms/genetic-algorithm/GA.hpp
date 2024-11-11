#ifndef __GA__
#define __GA__

#include "../../cube/CUBE.hpp"
#include "../../functions/objective-function/OBJECTIVE-FUNCTION.hpp"
#include "../../functions/fitness-function/FITNESS-FUNCTION.hpp"

class GA
{
private:
    vector<CUBE> population;
    OBJECTIVE_FUNCTION obj_func;
    FITNESS_FUNCTION fit_func;

    int population_size;
    int iteration;

public:
    GA(int pop_size = 123, int iter = 55, int obj = 0, int fit = 0);

    void SET_POPULATION_SIZE(int pop_size);
    void SET_ITERATION(int iter);
    void RUN(bool output = false);
};

#endif