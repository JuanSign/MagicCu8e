#ifndef __SA__
#define __SA__

#include "../../cube/CUBE.hpp"
#include "../../functions/objective-function/OBJECTIVE-FUNCTION.hpp"
#include "../../functions/scheduling-function/SCHEDULING-FUNCTION.hpp"

class SA
{
private:
    CUBE cube;
    OBJECTIVE_FUNCTION obj_func;
    SCHEDULING_FUNCTION sched_func;

    vector<double> difference_history;
    vector<double> time_history;
    vector<int> obj_score;

    tuple<int, int, int> GENERATE_NEIGHBOR();
    bool CHECK_PROBABILITY(double prob);

public:
    SA(CUBE cube, int obj = 0, int sched = 0);

    void SET_CUBE(CUBE cube);
    void SET_OBJ(int obj = 0);
    void SET_SCHED(int sched = 0, int alpha = 0);
    void RUN(bool output = false);
};

#endif