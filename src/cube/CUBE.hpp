#ifndef __CUBE__
#define __CUBE__

#include <array>
#include <vector>

using namespace std;

class CUBE
{
private:
    array<array<array<int, 5>, 5>, 5> data;

    void GENERATE_POSITIONS();
    void GENERATE_CONSTRAINTS();

public:
    array<array<int, 3>, 125> positions;
    array<array<int, 5>, 109> constraints;
    array<vector<int>, 125> adjacency_list;

    CUBE(int seed = 0);
    void SWAP(int i, int j);
    void PRINT_CUBE();
    void PRINT_CONSTRAINS();
};

#endif