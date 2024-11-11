#include "SA.hpp"

#include <iostream>
#include <cmath>
#include <random>
#include <set>
#include <fstream>
#include <filesystem>
#include <chrono>

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

void SA::RUN(bool log)
{
    // logging
    string directoryPath = "log/SA__";
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
    string deltaEPath = directoryPath + "/deltaE.txt";
    string tempPath = directoryPath + "/temp.txt";
    string probabilityPath = directoryPath + "/probability.txt";
    string verdictPath = directoryPath + "/verdict.txt";

    // ofstream objects
    ofstream F_cube(cubePath);
    ofstream F_status(statusPath);
    ofstream F_score(scorePath);
    ofstream F_swap(swapPath);
    ofstream F_time(timePath);
    ofstream F_deltaE(deltaEPath);
    ofstream F_temp(tempPath);
    ofstream F_prob(probabilityPath);
    ofstream F_verdict(verdictPath);

    // time counter
    chrono::high_resolution_clock::time_point start, end;
    chrono::microseconds duration;
    double mili;

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

    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    mili = duration.count();

    F_time << mili << '\n';
    F_deltaE << 0 << '\n';
    F_temp << this->sched_func.GET_INITIAL() << '\n';
    F_prob << 1 << '\n';
    F_verdict << "YES" << '\n';

    double total = mili;

    int iteration = 0;
    while (true)
    {
        start = chrono::high_resolution_clock::now();
        iteration++;
        double T = this->sched_func.CALCULATE(iteration);
        tuple<int, int, int> neighbor = this->GENERATE_NEIGHBOR();
        int deltaE = this->obj_func.CALCULATE(this->cube) - get<2>(neighbor);

        string verdict;
        if (deltaE > 0)
        {
            this->cube.SWAP(get<0>(neighbor), get<1>(neighbor));
            verdict = "YES";
        }
        else
        {
            double prob = exp(deltaE / T);
            if (CHECK_PROBABILITY(prob))
            {
                this->cube.SWAP(get<0>(neighbor), get<1>(neighbor));
                verdict = "YES";
            }
            else
                verdict = "NO";
        }
        end = chrono::high_resolution_clock::now();

        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        mili = duration.count();

        // output to stdout
        cout << "SA ITERATION-" << iteration << " " << mili << " ms." << endl;

        // log every iteration
        for (int i : this->cube.RESHAPE())
            F_cube << i << " ";
        F_cube << '\n';
        for (int i : this->cube.GET_STATUS())
            F_status << i << " ";
        F_status << '\n';

        F_score << this->obj_func.CALCULATE(this->cube) << '\n';
        F_swap << get<0>(neighbor) << " " << get<1>(neighbor) << '\n';
        F_time << mili << '\n';
        F_deltaE << deltaE << '\n';
        F_temp << T << '\n';
        F_prob << min(exp(deltaE / T), 1.0) << '\n';
        F_verdict << verdict << '\n';

        total += mili;

        if (fabs(T) < 1e-4)
            break;
        ;
    }
    F_cube.close();
    F_status.close();
    F_score.close();
    F_swap.close();
    F_time.close();
    F_deltaE.close();
    F_temp.close();
    F_prob.close();
    F_verdict.close();

    cout << "FINISHED IN: " << total << " ms." << endl;
}
