#include "HCSA.hpp"

#include <chrono>
#include <climits>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <numeric>

using namespace std;

HCSA::HCSA(CUBE cube, int opt)
{
    this->cube = cube;
    this->obj_func.SET_OPTION(opt);
}

void HCSA::SET_CUBE(CUBE cube) { this->cube = cube; }
void HCSA::SET_OPTION(int opt) { this->obj_func.SET_OPTION(opt); }

pair<int, int> HCSA::FIND_BEST()
{
    pair<int, int> res;
    int best = INT_MAX;
    for (int i = 1; i <= 124; i++)
    {
        for (int j = i + 1; j <= 125; j++)
        {
            this->cube.SWAP(i, j);
            int cur = this->obj_func.CALCULATE(this->cube);
            if (cur < best)
            {
                best = cur;
                res = {i, j};
            }
            this->cube.SWAP(i, j);
        }
    }
    return res;
}

void HCSA::RUN(bool log)
{
    // logging
    string directoryPath = "log/HCSA__";
    // time-tracking
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm tm = *localtime(&currentTime);
    char time[20];
    strftime(time, sizeof(time), "%d-%m-%Y__%H%M%S", &tm);
    directoryPath += time;
    filesystem::create_directory(directoryPath);

    // path to store log
    string cubePath = directoryPath + "/cube.txt";
    string statusPath = directoryPath + "/status.txt";
    string scorePath = directoryPath + "/score.txt";
    string swapPath = directoryPath + "/swap.txt";

    // ofstream objects
    ofstream F_cube(cubePath);
    ofstream F_status(statusPath);
    ofstream F_score(scorePath);
    ofstream F_swap(swapPath);

    // log initial state
    for (int i : this->cube.RESHAPE())
        F_cube << i << " ";
    F_cube << '\n';
    for (int i : this->cube.GET_STATUS())
        F_status << i << " ";
    F_status << '\n';
    F_score << this->obj_func.CALCULATE(this->cube) << '\n';
    F_swap << -1 << " " << -1 << '\n';

    int iteration = 0;
    while (true)
    {
        iteration++;
        pair<int, int> bestSwap = this->FIND_BEST();
        int curScore = this->obj_func.CALCULATE(this->cube);
        this->cube.SWAP(bestSwap.first, bestSwap.second);
        int newScore = this->obj_func.CALCULATE(this->cube);
        if (newScore >= curScore)
        {
            this->cube.SWAP(bestSwap.first, bestSwap.second);
            return;
        }

        // output to stdout
        cout << "HSCA ITERATION-" << iteration << " " << curScore << " " << newScore << endl;
        // log every iteration
        for (int i : this->cube.RESHAPE())
            F_cube << i << " ";
        F_cube << '\n';
        for (int i : this->cube.GET_STATUS())
            F_status << i << " ";
        F_status << '\n';
        F_score << newScore << '\n';
        F_swap << bestSwap.first << " " << bestSwap.second << '\n';
    }

    // close ofstream objects
    F_cube.close();
    F_status.close();
    F_score.close();
    F_swap.close();
}