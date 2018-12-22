#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector< vector< unsigned int > > sons(50000, vector<unsigned int>());
vector<unsigned int> depth(50000);
vector<unsigned int> parent(50000);
vector<unsigned int> snm(50000);
vector<unsigned int> myLog(50000);
vector< vector< unsigned int > > jump(17, vector<unsigned int>());
unsigned int logn;

unsigned int get(unsigned int v)
{
    unsigned int res = v;
    while (snm[res] != res)
    {
        res = snm[res];
    }
    unsigned int temp;
    while (snm[v] != res)
    {
        temp = snm[v];
        snm[v] = res;
        v = temp;
    }
    return res;
}

void unite(unsigned int v, unsigned int u) //(к чему, что)
{
    snm[u] = get(v);
}

void dfs(unsigned int v, unsigned int p, unsigned int d)
{
    depth[v] = d;
    parent[v] = p;
    for (size_t i = 0; i < sons[v].size(); ++i)
    {
        dfs(sons[v][i], v, d + 1);
    }
}

void dfsUpdate(unsigned int v, unsigned int d)
{
    for (size_t i = myLog[depth[v]] + 1; i < logn; ++i)
    {
        jump[i][v] = jump[i - 1][jump[i - 1][v]];
    }
    depth[v] = d;
    for (size_t i = 0; i < sons[v].size(); ++i)
    {
        dfsUpdate(sons[v][i], d + 1);
    }
}

int main()
{
    freopen("lca3.in", "r", stdin);
    freopen("lca3.out", "w", stdout);
    size_t n;
    cin >> n;
    for (size_t i = 0; i < n; ++i)
    {
        myLog[i] = (unsigned int)floor(log2((double)i));
    }
    vector<unsigned int> startRoots;
    unsigned int v;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> v;
        if (!v)
        {
            startRoots.push_back(i);
            snm[i] = i;
        }
        else
        {
            sons[v - 1].push_back(i);
            snm[i] = v - 1;
        }
    }
    for (size_t i = 0; i < startRoots.size(); ++i)
    {
        dfs(startRoots[i], startRoots[i], 0);
    }
    logn = (unsigned int)log2((double)n) + 1;
    for (size_t i = 0; i < n; ++i)
    {
        jump[0].push_back(parent[i]);
    }
    for (size_t i = 1; i < logn; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            jump[i].push_back(jump[i - 1][jump[i - 1][j]]);
        }
    }
    size_t m;
    cin >> m;
    unsigned int u, w, type, ans = 0, x, y;
    for (size_t j = 0; j < m; ++j)
    {
        cin >> type >> x >> y;
        u = (x - 1 + ans) % n;
        w = (y - 1 + ans) % n;
        if (type)
        {
            unite(w, u);
            parent[u] = w;
            jump[0][u] = w;
            sons[w].push_back(u);
            dfsUpdate(u, depth[w] + 1);
        }
        else
        {
            if (get(u) != get(w))
            {
                ans = 0;
                cout << ans << endl;
                continue;
            }
            if (depth[u] > depth[w])
            {
                swap(u, w);
            }
            for (size_t i = logn; i > 0; --i)
            {
                if (depth[w] - depth[u] >= (1 << (i - 1)))
                {
                    w = jump[i - 1][w];
                }
            }
            if (w == u)
            {
                ans = w + 1;
                cout << ans << endl;
                continue;
            }
            for (size_t i = logn; i > 0; --i)
            {
                if (jump[i - 1][w] != jump[i - 1][u])
                {
                    w = jump[i - 1][w];
                    u = jump[i - 1][u];
                }
            }
            ans = jump[0][u] + 1;
            cout << ans << endl;
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
