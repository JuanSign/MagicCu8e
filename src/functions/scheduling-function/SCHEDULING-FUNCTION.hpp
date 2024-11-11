#ifndef __SCHED_FUNC__
#define __SCHED_FUNC__

class SCHEDULING_FUNCTION
{
private:
    int option;
    double temperature;
    double alpha;

    double OPTION_0(int iteration); // exponential, T0 = 1000 | alpha = 0.99
    double OPTION_1(int iteration); // linear, T0 = 1000 | alpha = 1
    double OPTION_2(int iteration); // geometric, T0 = 1000 | alpha = 0.01
    double OPTION_3(int iteration); // logarithmic, T0 = 1000 | alpha = 5
    double OPTION_4(int iteration); // cauchy, T0 = 1000
    double OPTION_5(int iteration); // kirkpatrick, T0 = 1000

public:
    SCHEDULING_FUNCTION(int option = 0, double initial_temp = 100);

    void SET_OPTION(int option = 0, double initial_temp = 100);
    void SET_ALPHA(double alpha);
    double CALCULATE(int iteration);
    double GET_INITIAL();
};

#endif