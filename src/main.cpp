#include "algorithms/genetic-algorithm/GA.hpp"
#include "algorithms/hill-climbings/HCSA.hpp"
#include "algorithms/simulated-annealing/SA.hpp"
#include "cube/CUBE.hpp"

int main()
{
    CUBE c(1);
    SA algo(c);
    algo.RUN();
}