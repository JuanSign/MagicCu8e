#include "GA.hpp"

GA::GA(int pop_size, int iter, int obj, int fit)
{
    this->population_size = pop_size;
    this->iteration = iter;
    this->obj_func.SET_OPTION(obj);
    this->fit_func.SET_OPTION(fit);

    for (int i = 0; i < pop_size; i++)
    {
        CUBE c;
        population.push_back(c);
    }
}

void GA::SET_POPULATION_SIZE(int pop_size)
{
    this->population_size = pop_size;
    this->population.clear();
    for (int i = 0; i < pop_size; i++)
    {
        CUBE c;
        population.push_back(c);
    }
}

void GA::SET_ITERATION(int iter) { this->iteration = iter; }

void GA::RUN(bool output = false)
{
    for (int it = 0; it < this->iteration; it++)
    {
    }
}
