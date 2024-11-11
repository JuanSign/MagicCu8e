#include "algorithms/genetic-algorithm/GA.hpp"
#include "algorithms/hill-climbings/HCSA.hpp"
#include "algorithms/simulated-annealing/SA.hpp"
#include "cube/CUBE.hpp"

int main()
{
    // welcome to the playground...
    // HCSA := Hill Climbing Steepest Ascent
    // SA := Simulated Annealing
    // GA := Genetic Algorithm
    // CUBE := Magic Cube

    GA x(100, 1000);
    x.RUN();
}