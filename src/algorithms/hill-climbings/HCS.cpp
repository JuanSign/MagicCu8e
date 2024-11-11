#include "HCS.hpp"

#include <chrono>
#include <climits>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <random>

using namespace std;

HCS::HCS(CUBE cube, int opt, int nmax)
{
    this->cube = cube;
    this->obj_func.SET_OPTION(opt);
    this->NMAX = nmax;
}

void HCS::SET_CUBE(CUBE cube) { this->cube = cube; }
void HCS::SET_OPTION(int opt) { this->obj_func.SET_OPTION(opt); }

tuple<int, int, int> HCS::GENERATE_SWAP()
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

void HCS::RUN(bool log)
{
    // logging
    string directoryPath = "log/HCS__";
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
    string timePath = directoryPath + "/time.txt";

    // ofstream objects
    ofstream F_cube(cubePath);
    ofstream F_status(statusPath);
    ofstream F_score(scorePath);
    ofstream F_swap(swapPath);
    ofstream F_time(timePath);

    // time counter
    chrono::high_resolution_clock::time_point start, end;
    chrono::duration<double> duration;
    double seconds;

    start = chrono::high_resolution_clock::now();
    // log initial state
    for (int i : this->cube.RESHAPE())
        F_cube << i << " ";
    F_cube << '\n';
    for (int i : this->cube.GET_STATUS())
        F_status << i << " ";
    F_status << '\n';
    F_score << this->obj_func.CALCULATE(this->cube) << '\n';
    F_swap << -1 << " " << -1 << '\n';
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    seconds = duration.count();
    F_time << seconds << '\n';

    for (int iteration = 1; iteration <= this->NMAX; iteration++)
    {
        start = chrono::high_resolution_clock::now();
        iteration++;
        tuple<int, int, int> swapResult = this->GENERATE_SWAP();
        int curScore = this->obj_func.CALCULATE(this->cube);
        if (get<2>(swapResult) > curScore)
            continue;
        this->cube.SWAP(get<0>(swapResult), get<1>(swapResult));
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        seconds = duration.count();

        // output to stdout
        cout << "HCS ITERATION-" << iteration << " " << seconds << " s." << endl;

        // log every iteration
        for (int i : this->cube.RESHAPE())
            F_cube << i << " ";
        F_cube << '\n';
        for (int i : this->cube.GET_STATUS())
            F_status << i << " ";
        F_status << '\n';
        F_score << get<2>(swapResult) << '\n';
        F_swap << get<0>(swapResult) << " " << get<1>(swapResult) << '\n';
        F_time << seconds << '\n';
    }

    // close ofstream objects
    F_cube.close();
    F_status.close();
    F_score.close();
    F_swap.close();
}