#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

vector< vector<unsigned int> > sons(100000, vector<unsigned int>());
vector<unsigned int> depth(100000);
vector<int> price(100000);
vector<unsigned int> parent(100000);

void dfs(unsigned int v, unsigned int d)
{
    depth[v] = d;
    for (size_t i = 0; i < sons[v].size(); ++i)
    {
        dfs(sons[v][i], d + 1);
    }
}

int main()
{
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
    size_t n;
    cin >> n;
    unsigned int v;
    int p;
    for (size_t i = 1; i < n; ++i)
    {
        cin >> v >> p;
        sons[v - 1].push_back(i);
        parent[i] = v - 1;
        price[i] = p;
    }
    parent[0] = 0;
    price[0] = INT_MAX;
    dfs(0, 0);
    unsigned int logn = (unsigned int)log2((double)n) + 1;
    vector< vector< pair<unsigned int, int> > > jump(logn, vector< pair<unsigned int, int> >());
    for (size_t i = 0; i < n; ++i)
    {
        jump[0].push_back(make_pair(parent[i], price[i]));
    }
    for (size_t i = 1; i < logn; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            jump[i].push_back(make_pair(jump[i - 1][jump[i - 1][j].first].first, min(jump[i - 1][jump[i - 1][j].first].second, jump[i - 1][j].second)));
        }
    }
    size_t m;
    cin >> m;
    unsigned int u, w;
    int minimum;
    for (size_t j = 0; j < m; ++j)
    {
        minimum = INT_MAX;
        cin >> u >> w;
        --u;
        --w;
        if (depth[u] > depth[w])
        {
            swap(u, w);
        }
        for (size_t i = logn; i > 0; --i)
        {
            if (depth[w] - depth[u] >= (1 << (i - 1)))
            {
                minimum = min(jump[i - 1][w].second, minimum);
                w = jump[i - 1][w].first;
            }
        }
        if (w == u)
        {
            cout << minimum << endl;
            continue;
        }
        for (size_t i = logn; i > 0; --i)
        {
            if (jump[i - 1][w].first != jump[i - 1][u].first)
            {
                minimum = min(jump[i - 1][w].second, minimum);
                minimum = min(jump[i - 1][u].second, minimum);
                w = jump[i - 1][w].first;
                u = jump[i - 1][u].first;
            }
        }
        minimum = min(jump[0][u].second, minimum);
        minimum = min(jump[0][w].second, minimum);
        cout << minimum << endl;
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
