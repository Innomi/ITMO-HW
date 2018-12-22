#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>

#define MNOGO 1e5

using namespace std;

vector< unordered_map<unsigned int, int> > g;
vector< unordered_map<unsigned int, int> > rest;
vector<bool> visited;

unsigned int b;

int dfs(unsigned int v, int minC)
{
    if (v == b)
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

vector<bool> visitedForCut;

void dfsCut(unsigned int v, vector< pair<unsigned int, unsigned int> > & cut)
{
    visitedForCut[v] = true;
    for (auto i = rest[v].begin(); i != rest[v].end(); ++i)
    {
        if (visited[i->first] && !visitedForCut[i->first])
        {
            dfsCut(i->first, cut);
        }
        else
        {
            if (!visited[i->first])
            {
                cut.emplace_back(v, i->first);
            }
        }
    }
}

int main()
{
    unsigned int n, m, a, from, to;
    int d;
    char c;
    scanf("%u %u\n", &n, &m);
    vector< vector<char> > map(n, vector<char>(m));
    g.resize(n * m * 2, unordered_map<unsigned int, int>());
    rest.resize(n * m * 2, unordered_map<unsigned int, int>());
    visited.resize(n * m * 2, false);
    visitedForCut.resize(n * m * 2, false);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            c = getchar();
            map[i][j] = c;
            switch(c)
            {
                case '-':
                    d = MNOGO;
                    break;
                case 'A':
                    d = MNOGO;
                    a = (i * m + j) * 2;
                    break;
                case 'B':
                    d = MNOGO;
                    b = (i * m + j) * 2;
                    break;
                case '.':
                    d = 1;
                    break;
                case '#':
                    d = 0;
                    break;
            }
            from = (i * m + j) * 2 + 1;
            if (i != n - 1)
            {
                to = ((i + 1) * m + j) * 2;
                g[from][to] = MNOGO;
                g[to][from] = 0;
                rest[from][to] = 0;
                rest[to][from] = 0;
            }
            if (j != m - 1)
            {
                to = (i * m + j + 1) * 2;
                g[from][to] = MNOGO;
                g[to][from] = 0;
                rest[from][to] = 0;
                rest[to][from] = 0;
            }
            if (i != 0)
            {
                to = ((i - 1) * m + j) * 2;
                g[from][to] = MNOGO;
                g[to][from] = 0;
                rest[from][to] = 0;
                rest[to][from] = 0;
            }
            if (j != 0)
            {
                to = (i * m + j - 1) * 2;
                g[from][to] = MNOGO;
                g[to][from] = 0;
                rest[from][to] = 0;
                rest[to][from] = 0;
            }
            from = (i * m + j) * 2;
            to = (i * m + j) * 2 + 1;
            g[from][to] = d;
            g[to][from] = 0;
            rest[from][to] = 0;
            rest[to][from] = 0;
        }
        while ((c = getchar()) != '\n') {}
    }
    int flow(0), resDfs;
    while (true)
    {
        resDfs = dfs(a, INT_MAX);
        flow += resDfs;
        visited.assign(n * m * 2, false);
        if (!resDfs)
        {
            break;
        }
    }
    if (flow >= MNOGO)
    {
        printf("-1\n");
        return 0;
    }
    vector< pair<unsigned int, unsigned int> > cut;
    if (flow > 0)
    {
        dfs(a, 0);
        dfsCut(a, cut);

    }
    printf("%d\n", flow);
    unsigned int x, y;
    for (size_t i = 0; i < cut.size(); ++i)
    {
        x = (cut[i].first / 2) % m;
        y = (cut[i].first / 2) / m;
        if (g[cut[i].first][cut[i].second] == 1)
        {
            map[y][x] = '+';
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    return 0;
}

