#include "CUBE.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>

using namespace std;

void CUBE::GENERATE_POSITIONS()
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++)
                this->positions[this->data[i][j][k] - 1] = {i, j, k};
}

void CUBE::GENERATE_CONSTRAINTS()
{
    vector<vector<int>> constraints;

    vector<int> sd[4];
    for (int i = 0; i < 5; i++)
    {
        sd[0].push_back(this->data[i][i][i]);
        sd[1].push_back(this->data[i][i][4 - i]);
        sd[2].push_back(this->data[i][4 - i][i]);
        sd[3].push_back(this->data[i][4 - i][4 - i]);
    }
    for (int i = 0; i < 4; i++)
        constraints.push_back(sd[i]);

    vector<vector<int>> pd;
    for (int i = 0; i < 5; i++)
    {
        vector<int> cur_pd[2];
        for (int c = 0; c < 5; c++)
        {
            cur_pd[0].push_back(this->data[i][c][c]);
            cur_pd[1].push_back(this->data[i][c][4 - c]);
        }
        pd.push_back(cur_pd[0]);
        pd.push_back(cur_pd[1]);
    }
    for (int j = 0; j < 5; j++)
    {
        vector<int> cur_pd[2];
        for (int c = 0; c < 5; c++)
        {
            cur_pd[0].push_back(this->data[c][j][c]);
            cur_pd[1].push_back(this->data[c][j][4 - c]);
        }
        pd.push_back(cur_pd[0]);
        pd.push_back(cur_pd[1]);
    }
    for (int k = 0; k < 5; k++)
    {
        vector<int> cur_pd[2];
        for (int c = 0; c < 5; c++)
        {
            cur_pd[0].push_back(this->data[c][c][k]);
            cur_pd[1].push_back(this->data[c][4 - c][k]);
        }
        pd.push_back(cur_pd[0]);
        pd.push_back(cur_pd[1]);
    }
    for (int i = 0; i < 30; i++)
        constraints.push_back(pd[i]);

    vector<int> rows[25], columns[25], pillars[25];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                rows[5 * i + j].push_back(this->data[i][j][k]);
                columns[5 * i + k].push_back(this->data[i][j][k]);
                pillars[5 * j + k].push_back(this->data[i][j][k]);
            }
        }
    }
    for (int i = 0; i < 25; i++)
        constraints.push_back(rows[i]);
    for (int i = 0; i < 25; i++)
        constraints.push_back(columns[i]);
    for (int i = 0; i < 25; i++)
        constraints.push_back(pillars[i]);

    for (int i = 0; i < 109; i++)
        for (int j = 0; j < 5; j++)
            this->constraints[i][j] = constraints[i][j];
    for (int i = 0; i < 109; i++)
        for (int j = 0; j < 5; j++)
            this->adjacency_list[this->constraints[i][j] - 1].push_back(i);
}

CUBE::CUBE(int seed)
{
    vector<int> numbers(125);
    iota(numbers.begin(), numbers.end(), 1);

    random_device rd;
    mt19937 mt;
    if (seed)
        mt.seed(seed);
    else
        mt.seed(rd());
    shuffle(numbers.begin(), numbers.end(), mt);

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++)
                this->data[i][j][k] = numbers[25 * i + 5 * j + k];

    this->GENERATE_POSITIONS();
    this->GENERATE_CONSTRAINTS();
}

void CUBE::SWAP(int i, int j)
{
    array<int, 3> i_cord = this->positions[i - 1];
    array<int, 3> j_cord = this->positions[j - 1];

    for (int c = 0; c < 109; c++)
    {
        for (int &e : this->constraints[c])
        {
            if (e == i)
                e = j;
            else if (e == j)
                e = i;
        }
    }

    swap(this->data[i_cord[0]][i_cord[1]][i_cord[2]], this->data[j_cord[0]][j_cord[1]][j_cord[2]]);
    swap(this->adjacency_list[i - 1], this->adjacency_list[j - 1]);
    swap(this->positions[i - 1], this->positions[j - 1]);
}

void CUBE::PRINT_CUBE()
{
    cout << "---PRINTING CUBE---" << endl;
    for (int i = 4; i >= 0; i--)
    {
        cout << "LAYER " << i + 1 << endl;
        for (int j = 4; j >= 0; j--)
        {
            cout << "ROW " << j + 1 << ": ";
            for (int k = 0; k < 5; k++)
            {
                cout << this->data[i][j][k] << " ";
            }
            cout << endl;
        }
    }
    cout << "------" << endl;
}

void CUBE::PRINT_CONSTRAINS()
{
    cout << "---PRINTING CUBE'S constraints---" << endl;
    for (int i = 0; i < 109; i++)
    {
        if (i < 4)
            cout << "SPACE DIAGONALS: ";
        else if (i < 34)
            cout << "PLANE DIAGONALS: ";
        else if (i < 59)
            cout << "ROWS: ";
        else if (i < 84)
            cout << "COLUMNS: ";
        else
            cout << "PILLARS: ";

        for (int x = 0; x < 5; x++)
            cout << this->constraints[i][x] << " ";
        cout << endl;
    }
    cout << "------" << endl;
}

array<int, 125> CUBE::RESHAPE()
{
    array<int, 125> cube2d;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                cube2d[i * 25 + j * 5 + k] = this->data[i][j][k];
            }
        }
    }
}
