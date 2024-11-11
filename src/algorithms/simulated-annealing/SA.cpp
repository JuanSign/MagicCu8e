#include "SA.hpp"

#include <cmath>
#include <random>
#include <set>

using namespace std;

tuple<int, int, int> SA::GENERATE_NEIGHBOR()
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(1, 125);

    int num1 = dis(gen);
    int num2 = dis(gen);

    while (num1 == num2)
        num2 = dis(gen);

    this->cube.SWAP(num1, num2);
    int obj_score = this->obj_func.CALCULATE(this->cube);
    this->cube.SWAP(num1, num2);

    return {num1, num2, obj_score};
}

bool SA::CHECK_PROBABILITY(double prob)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    int x = dis(gen);
    return x <= prob * 100;
}

SA::SA(CUBE cube, int obj, int sched)
{
    this->cube = cube;
    this->obj_func.SET_OPTION(obj);
    this->sched_func.SET_OPTION(sched);
}

void SA::SET_CUBE(CUBE cube) { this->cube = cube; }

void SA::SET_OBJ(int obj) { this->obj_func.SET_OPTION(obj); }

void SA::SET_SCHED(int sched, int alpha)
{
    this->sched_func.SET_OPTION(sched);
    if (alpha)
        this->sched_func.SET_ALPHA(alpha);
}

void SA::RUN(bool output = false)
{
    int iteration = 1;
    while (true)
    {
        double T = this->sched_func.CALCULATE(iteration);
        tuple<int, int, int> neighbor = this->GENERATE_NEIGHBOR();
        int deltaE = this->obj_func.CALCULATE(this->cube) - get<2>(neighbor);
        if (deltaE > 0)
        {
            this->cube.SWAP(get<0>(neighbor), get<1>(neighbor));
        }
        else
        {
            double prob = exp(-deltaE / T);
            if (CHECK_PROBABILITY(prob))
            {
                this->cube.SWAP(get<0>(neighbor), get<1>(neighbor));
            }
        }
    }
}
