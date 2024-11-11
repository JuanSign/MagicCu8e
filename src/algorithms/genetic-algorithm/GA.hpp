#ifndef __GA__
#define __GA__

#include "../../cube/CUBE.hpp"
#include "../../functions/objective-function/OBJECTIVE-FUNCTION.hpp"
#include "../../functions/fitness-function/FITNESS-FUNCTION.hpp"

class GA
{
private:
    vector<CUBE> population;
    FITNESS_FUNCTION fit_func;

    vector<int> fit_score;

    int population_size;
    int iteration;

    bool CHECK_PROBABILITY(double prob);
    double GENERATE_PROBABILITY();

    pair<int, int> CHOOSE_PARENT();
    array<int, 125> REPRODUCE(CUBE c1, CUBE c2);
    void MUTATE(CUBE &cube);

public:
    GA(int pop_size = 123, int iter = 55, int fit = 0);

    void SET_POPULATION_SIZE(int pop_size);
    void SET_ITERATION(int iter);
    void RUN(bool log = false);
};

#endif