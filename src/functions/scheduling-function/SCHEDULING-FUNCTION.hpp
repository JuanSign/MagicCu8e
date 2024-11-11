#ifndef __SCHED_FUNC__
#define __SCHED_FUNC__

class SCHEDULING_FUNCTION
{
private:
    int option;
    double temperature;
    double alpha;

    double OPTION_0(int iteration);
    double OPTION_1(int iteration);
    double OPTION_2(int iteration);

public:
    SCHEDULING_FUNCTION(int option = 0, double initial_temp = 1000);

    void SET_OPTION(int option = 0, double initial_temp = 1000);
    void SET_ALPHA(double alpha);
    double CALCULATE(int iteration);
};

#endif