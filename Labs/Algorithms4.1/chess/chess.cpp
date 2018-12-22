#include <iostream>
#include <climits>
#include <vector>

using namespace std;

vector<bool> usedLeft;
vector< vector<unsigned int> > edges;
vector<unsigned int> toLeft;
vector<unsigned int> diagonals1;
vector<unsigned int> diagonals2;

//ctrl+c, ctrl+v from Discr3.3/matching/matching.cpp
bool tryTyan(unsigned int v)
{
    if (usedLeft[v])
    {
        return false;
    }
    usedLeft[v] = true;
    for (size_t i = 0; i < edges[v].size(); ++i)
    {
        unsigned int toRight = edges[v][i];
        if (toLeft[toRight] == UINT_MAX || tryTyan(toLeft[toRight]))
        {
            toLeft[toRight] = v;
            return true;
        }
    }
    return false;
}

int count()
{
    unsigned int amount(0);
    for (size_t i = 0; i < usedLeft.size(); ++i)
    {
        usedLeft.assign(usedLeft.size(), false);
        if (tryTyan(i))
        {
            ++amount;
        }
    }
    return amount;
}

void getDiagonals()
{
    usedLeft.assign(usedLeft.size(), false);
    vector<unsigned int> toRight(toLeft.size(), UINT_MAX);
    for (size_t i = 0; i < toLeft.size(); ++i)
    {
        if (toLeft[i] != UINT_MAX)
        {
            toRight[toLeft[i]] = i;
        }
    }
    for (size_t i = 0; i < toRight.size(); ++i)
    {
        if (toRight[i] == UINT_MAX)
        {
            tryTyan(i);
        }
    }
    for (size_t i = 0; i < toLeft.size(); ++i)
    {
        if (toRight[i] != UINT_MAX && !usedLeft[i])
        {
            diagonals1.emplace_back(i);
        }
        if (toLeft[i] != UINT_MAX && usedLeft[toLeft[i]])
        {
            diagonals2.emplace_back(i);
        }
    }
}

//Хочется выразить огромную благодарность г-ну Кёнигу. Спасибо, что вы были!
//См. теорему о величине максимального паросочетания и минимального
//вершинного покрытия.

int main()
{
    unsigned int n, m, minAmount, amount, color(1);
    scanf("%u %u\n", &n, &m);
    vector< vector<char> > board(n, vector<char>(m));
    edges.assign(n + m - 1, vector<unsigned int>());
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            board[i][j] = getchar();
            if ((board[i][j] ^ i ^ j) & 1)
            {
                edges[j + i].emplace_back(m - 1 + i - j);
            }
        }
        if (i < n - 1)
        {
            while (getchar() != '\n') {}
        }
    }
    usedLeft.resize(n + m - 1);
    toLeft.resize(n + m - 1, UINT_MAX);
    minAmount = count();
    getDiagonals();
    edges.assign(n + m - 1, vector<unsigned int>());
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            if (!((board[i][j] ^ i ^ j) & 1))
            {
                edges[j + i].emplace_back(m - 1 + i - j);
            }
        }
    }
    toLeft.assign(n + m - 1, UINT_MAX);
    amount = count();
    if (minAmount > amount)
    {
        minAmount = amount;
        diagonals1.clear();
        diagonals2.clear();
        getDiagonals();
        color = 0;
    }
    printf("%u\n", minAmount);
    int x, y;
    for (size_t i = 0; i < diagonals1.size(); ++i)
    {
        x = max(0, (int)diagonals1[i] - (int)m + 1) + 1;
        y = min((int)m - 1, (int)diagonals1[i]) + 1;
        printf("1 %d %u %c\n", x, y, ((color ^ x ^ y) & 1) ? 'B' : 'W');
    }
    for (size_t i = 0; i < diagonals2.size(); ++i)
    {
        x = max(0, (int)diagonals2[i] - (int)m + 1) + 1;
        y = max(0, (int)m - (int)diagonals2[i] - 1) + 1;
        printf("2 %d %d %c\n", x, y, ((color ^ x ^ y) & 1) ? 'B' : 'W');
    }
    return 0;
}
