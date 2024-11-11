#include "GA.hpp"

#include <algorithm>
#include <random>
#include <set>

bool GA::CHECK_PROBABILITY(double prob)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    int x = dis(gen);
    return x <= prob * 100;
}

double GA::GENERATE_PROBABILITY()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    double x = dis(gen);
    x /= 100;
    return x;
}

pair<int, int> GA::CHOOSE_PARENT()
{
    pair<int, int> parents;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, population_size - 1);

    double maks = *max_element(this->fit_score.begin(), this->fit_score.end());
    maks *= (1.3);

    while (true)
    {
        int id = dis(gen);
        double prob = this->fit_score[id];
        prob /= maks;
        if (this->CHECK_PROBABILITY(1 - prob))
        {
            parents.first = id;
            break;
        }
    }

    while (true)
    {
        int id = dis(gen);
        if (id == parents.first)
            continue;
        double prob = this->fit_score[id];
        prob /= maks;
        if (this->CHECK_PROBABILITY(1 - prob))
        {
            parents.second = id;
            break;
        }
    }

    return parents;
}

array<int, 125> GA::REPRODUCE(CUBE c1, CUBE c2)
{
    array<int, 125> p1 = c1.RESHAPE();
    array<int, 125> p2 = c2.RESHAPE();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(25, 101);

    int cross_point = dis(gen);

    array<int, 125> child;
    set<int> taken;
    vector<int> secondHalf;

    for (int i = 0; i < cross_point; i++)
    {
        child[i] = p1[i];
        taken.insert(p1[i]);
    }

    for (int i = cross_point; i < 125; i++)
    {
        if (taken.count(p2[i]) == 0)
        {
            secondHalf.push_back(p2[i]);
            taken.insert(p2[i]);
        }
        if (taken.count(p1[i]) == 0)
        {
            secondHalf.push_back(p1[i]);
            taken.insert(p1[i]);
        }
    }

    for (int i = cross_point; i < 125; i++)
    {
        child[i] = secondHalf[i - cross_point];
    }

    return child;
}

void GA::MUTATE(CUBE &cube)
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(1, 125);

    int num1 = dis(gen);
    int num2 = dis(gen);

    while (num1 == num2)
        num2 = dis(gen);

    cube.SWAP(num1, num2);
}

GA::GA(int pop_size, int iter, int fit)
{
    this->population_size = pop_size;
    this->iteration = iter;
    this->fit_func.SET_OPTION(fit);

    for (int i = 0; i < pop_size; i++)
    {
        CUBE c;
        population.push_back(c);
        this->fit_score.push_back(this->fit_func.CALCULATE(c));
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

void GA::RUN(bool output)
{
    vector<int>::iterator it = min_element(this->fit_score.begin(), this->fit_score.end());
    int cubeID = distance(this->fit_score.begin(), it);
    int bestFit = *it;

    for (int it = 0; it < this->iteration; it++)
    {
        vector<CUBE> newPopulation;
        for (int child = 0; child < population_size; child++)
        {
            pair<int, int> parents = this->CHOOSE_PARENT();
            array<int, 125> c = this->REPRODUCE(this->population[parents.first], this->population[parents.second]);
            CUBE ch(c);

            double mutate_prob = GENERATE_PROBABILITY();
            if (CHECK_PROBABILITY(mutate_prob))
            {
                this->MUTATE(ch);
            }
            newPopulation.push_back(ch);
        }
        for (int i = 0; i < newPopulation.size(); i++)
        {
            population.push_back(newPopulation[i]);
            if (this->fit_func.CALCULATE(newPopulation[i]) < bestFit)
            {
                bestFit = this->fit_func.CALCULATE(newPopulation[i]);
                cubeID = population_size + i;
            }
        }
        population_size = this->population.size();
    }
}
