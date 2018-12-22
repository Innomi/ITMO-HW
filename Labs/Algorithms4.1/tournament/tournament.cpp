#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

vector< unordered_map<unsigned int, int> > g;
vector< unordered_map<unsigned int, int> > rest;
vector<bool> visited;

int dfs(unsigned int v, int minC)
{
    if (v == rest.size() - 1)
    {
        return minC;
    }
    visited[v] = true;
    for (auto i = rest[v].begin(); i != rest[v].end(); ++i)
    {
        if (!visited[i->first] && g[v][i->first] > i->second)
        {
            int d = dfs(i->first, min(minC, g[v][i->first] - i->second));
            if (d > 0)
            {
                i->second += d;
                rest[i->first][v] -= d;
                return d;
            }
        }
    }
    return 0;
}

//Я не виноват!!!
//Я не хотел участвовать в этой коррупционной схеме, меня заставили!
//Они говорили, что убъют моих жену и детей, если я им не помогу! =(

int main()
{
    unsigned int n;
    char c;
    scanf("%u\n", &n);
    g.resize(n + 2, unordered_map<unsigned int, int>());
    rest.resize(n + 2, unordered_map<unsigned int, int>());
    visited.resize(n + 2, false);
    vector< vector<char> > table(n, vector<char>(n));
    for (size_t i = 0; i < n; ++i)
    {
        g[0][i + 1] = 0;
        g[i + 1][0] = 0;
        g[i + 1][n + 1] = 0;
        g[n + 1][i + 1] = 0;
        rest[0][i + 1] = 0;
        rest[i + 1][0] = 0;
        rest[i + 1][n + 1] = 0;
        rest[n + 1][i + 1] = 0;
        for (size_t j = 0; j < n; ++j)
        {
            c = getchar();
            table[i][j] = c;
            switch (c)
            {
                case '.':
                    if (j > i)
                    {
                        g[0][i + 1] += 3;
                        g[i + 1][j + 1] = 3;
                        g[j + 1][i + 1] = 0;
                        rest[i + 1][j + 1] = 0;
                        rest[j + 1][i + 1] = 0;
                    }
                    break;
                case 'W':
                    --g[i + 1][n + 1];
                case 'w':
                    --g[i + 1][n + 1];
                case 'l':
                    --g[i + 1][n + 1];
            }
        }
        while ((c = getchar()) != '\n') {}
    }
    int k;
    for (size_t i = 0; i < n; ++i)
    {
        scanf("%d", &k);
        g[i + 1][n + 1] += k;
    }
    int flow(0), resDfs;
    while (true)
    {
        resDfs = dfs(0, INT_MAX);
        if (!resDfs)
        {
            break;
        }
        flow += resDfs;
        visited.assign(n + 2, false);
    }
    int points;
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (table[i][j] == '.')
            {
                points = rest[i + 1][j + 1];
                switch (points)
                {
                    case 3:
                        table[i][j] = 'L';
                        table[j][i] = 'W';
                        break;
                    case 2:
                        table[i][j] = 'l';
                        table[j][i] = 'w';
                        break;
                    case 1:
                        table[i][j] = 'w';
                        table[j][i] = 'l';
                        break;
                    case 0:
                        table[i][j] = 'W';
                        table[j][i] = 'L';
                        break;
                }
            }
            printf("%c", table[i][j]);
        }
        printf("\n");
    }
    return 0;
}
