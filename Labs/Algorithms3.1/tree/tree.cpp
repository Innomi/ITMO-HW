#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector< vector< pair<unsigned int, int> > > edges(200000, vector< pair<unsigned int, int> >());
vector<unsigned int> depth(200000);
vector<int> price(200000);
vector<unsigned int> parent(200000);

void dfs(unsigned int v, unsigned int p, unsigned int d, int w)
{
    depth[v] = d;
    parent[v] = p;
    price[v] = w;
    for (size_t i = 0; i < edges[v].size(); ++i)
    {
        if (edges[v][i].first != p)
        {
            dfs(edges[v][i].first, v, d + 1, edges[v][i].second);
        }
    }
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    size_t n;
    cin >> n;
    unsigned int v1, v2;
    int p;
    for (size_t i = 1; i < n; ++i)
    {
        cin >> v1 >> v2 >> p;
        edges[v1].push_back(make_pair(v2, p));
        edges[v2].push_back(make_pair(v1, p));
    }
    parent[0] = 0;
    price[0] = 0;
    dfs(0, 0, 0, 0);
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
            jump[i].push_back(make_pair(jump[i - 1][jump[i - 1][j].first].first, jump[i - 1][jump[i - 1][j].first].second + jump[i - 1][j].second));
        }
    }
    size_t m;
    cin >> m;
    unsigned int u, w;
    int sum;
    for (size_t j = 0; j < m; ++j)
    {
        sum = 0;
        cin >> u >> w;
        if (depth[u] > depth[w])
        {
            swap(u, w);
        }
        for (size_t i = logn; i > 0; --i)
        {
            if (depth[w] - depth[u] >= (1 << (i - 1)))
            {
                sum += jump[i - 1][w].second;
                w = jump[i - 1][w].first;
            }
        }
        if (w == u)
        {
            cout << sum << endl;
            continue;
        }
        for (size_t i = logn; i > 0; --i)
        {
            if (jump[i - 1][w].first != jump[i - 1][u].first)
            {
                sum += jump[i - 1][w].second;
                sum += jump[i - 1][u].second;
                w = jump[i - 1][w].first;
                u = jump[i - 1][u].first;
            }
        }
        sum += jump[0][u].second;
        sum += jump[0][w].second;
        cout << sum << endl;
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
