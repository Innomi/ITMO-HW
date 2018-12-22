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
    freopen("cut.in", "r", stdin);
    freopen("cut.out", "w", stdout);
    unsigned int n, m, a, b;
    int c;
    scanf("%u\n%u", &n, &m);
    g.resize(n, unordered_map<unsigned int, int>());
    rest.resize(n, unordered_map<unsigned int, int>());
    visited.resize(n, false);
    visitedForCut.resize(n, false);
    vector< pair<unsigned int, unsigned int> > tubes;
    vector<int> cs;
    for (size_t i = 0; i < m; ++i)
    {
        scanf("%u %u %d", &a, &b, &c);
        --a;
        --b;
        tubes.emplace_back(a, b);
        cs.emplace_back(c);
        g[a][b] = c;
        g[b][a] = c;
        rest[a][b] = 0;
        rest[b][a] = 0;
    }
    int flow(0), resDfs;
    while (true)
    {
        resDfs = dfs(0, INT_MAX);
        flow += resDfs;
        for (size_t i = 0; i < n; ++i)
        {
            visited[i] = false;
        }
        if (!resDfs)
        {
            break;
        }
    }
    vector< pair<unsigned int, unsigned int> > cut;
    dfs(0, 0);
    dfsCut(0, cut);
    printf("%d %d\n", cut.size(), flow);
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < cut.size(); ++j)
        {
            if (tubes[i] == cut[j] || 
                    tubes[i].first == cut[j].second && 
                    tubes[i].second == cut[j].first)
            {
                printf("%u ", i + 1);
                break;
            }
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}

