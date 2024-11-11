#include "GA.hpp"

#include <iostream>
#include <algorithm>
#include <random>
#include <set>
#include <numeric>
#include <chrono>
#include <filesystem>
#include <string>
#include <fstream>

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
        this->population.push_back(c);
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

void GA::RUN(bool log)
{
    // logging
    string directoryPath = "log/GA__";
    // time-tracking
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm tm = *localtime(&currentTime);
    char time[20];
    strftime(time, sizeof(time), "%d-%m-%Y__%H%M%S", &tm);
    directoryPath += time;
    filesystem::create_directory(directoryPath);

    string bestCubePath = directoryPath + "/best-cube.txt";
    string bestScorePath = directoryPath + "/best-score.txt";
    string avgScorePath = directoryPath + "/avg-score.txt";
    string statusPath = directoryPath + "/status.txt";
    string timePath = directoryPath + "/time.txt";

    ofstream F_BCube(bestCubePath);
    ofstream F_BScore(bestScorePath);
    ofstream F_AScore(avgScorePath);
    ofstream F_Status(statusPath);
    ofstream F_Time(timePath);

    chrono::high_resolution_clock::time_point start, end;
    chrono::duration<double> duration;
    double seconds;

    vector<int>::iterator it = min_element(this->fit_score.begin(), this->fit_score.end());
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, population_size - 1);

    start = chrono::high_resolution_clock::now();
    int bestScore = *min_element(this->fit_score.begin(), this->fit_score.end());
    int id = distance(this->fit_score.begin(), min_element(this->fit_score.begin(), this->fit_score.end()));
    double avgScore = accumulate(fit_score.begin(), fit_score.end(), 0) / (double)this->population_size;
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    seconds = duration.count();

    for (int i : this->population[id].RESHAPE())
        F_BCube << i << " ";
    F_BCube << '\n';
    F_BScore << bestScore << '\n';
    F_AScore << avgScore << '\n';
    for (int i : this->population[id].GET_STATUS())
        F_Status << i << " ";
    F_Status << '\n';
    F_Time << seconds << '\n';

    for (int it = 1; it <= this->iteration; it++)
    {
        start = chrono::high_resolution_clock::now();
        vector<CUBE> newPopulation;
        for (int i = 1; i <= population_size; i++)
        {
            pair<int, int> parents = this->CHOOSE_PARENT();
            array<int, 125> c = this->REPRODUCE(this->population[parents.first], this->population[parents.second]);
            CUBE child(c);

            double mutate_prob = GENERATE_PROBABILITY();
            if (CHECK_PROBABILITY(mutate_prob))
            {
                this->MUTATE(child);
            }
            newPopulation.push_back(child);
        }
        int randID = dis(gen);
        newPopulation[randID] = this->population[id];

        this->population = newPopulation;
        for (int i = 0; i < population_size; i++)
            this->fit_score[i] = this->fit_func.CALCULATE(this->population[i]);

        bestScore = *min_element(this->fit_score.begin(), this->fit_score.end());
        id = distance(this->fit_score.begin(), min_element(this->fit_score.begin(), this->fit_score.end()));
        avgScore = accumulate(fit_score.begin(), fit_score.end(), 0) / (double)this->population_size;
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        seconds = duration.count();

        for (int i : this->population[id].RESHAPE())
            F_BCube << i << " ";
        F_BCube << '\n';
        F_BScore << bestScore << '\n';
        F_AScore << avgScore << '\n';
        for (int i : this->population[id].GET_STATUS())
            F_Status << i << " ";
        F_Status << '\n';
        F_Time << seconds << '\n';
        cout << "GA ITERATION-" << it << " " << seconds << " s." << endl;
    }

    F_BCube.close();
    F_BScore.close();
    F_AScore.close();
    F_Status.close();
    F_Time.close();
}
