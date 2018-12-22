#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector< vector<unsigned int> > edges(100000, vector<unsigned int>());
vector<unsigned int> path;
vector<unsigned int> depth;
vector<unsigned int> index(100000);
unsigned int maxI = 0;

void dfs(unsigned int v, unsigned int d, unsigned int p)
{
    index[v] = depth.size();
    if (index[v] > maxI)
    {
        maxI = index[v];
    }
    path.push_back(v);
    depth.push_back(d);
    for (size_t i = 0; i < edges[v].size(); ++i)
    {
        if (edges[v][i] != p)
        {
            dfs(edges[v][i], d + 1, v);
            path.push_back(v);
            depth.push_back(d);
        }
    }
    if (!edges[v].size())
    {
        path.push_back(v);
        depth.push_back(d);
    }
}

int main()
{
    freopen("dynamic.in", "r", stdin);
    freopen("dynamic.out", "w", stdout);
    size_t n = 1;
    while (n != 0)
    {
        path.clear();
        depth.clear();
        maxI = 0;
        for (size_t i = 0; i < 100000; ++i)
        {
            edges[i].clear();
        }
        cin >> n;
        unsigned int v, u;
        for (size_t i = 1; i < n; ++i)
        {
            cin >> v >> u;
            edges[v - 1].push_back(u - 1);
            edges[u - 1].push_back(v - 1);
        }
        dfs(0, 0, 0);
        ++maxI;
        vector<unsigned int> log(maxI + 1);
        log[0] = 0;
        for (size_t i = 1; i <= maxI; ++i)
        {
            log[i] = (unsigned int)floor(log2((double)i));
        }
        vector< vector< pair<unsigned int, unsigned int> > > st(log[maxI] + 1, vector< pair<unsigned int, unsigned int> >());
        for (size_t i = 0; i < maxI; ++i)
        {
            st[0].push_back(make_pair(depth[i], path[i]));
        }
        unsigned int two = 1;
        for (size_t i = 1; i <= log[maxI]; ++i)
        {
            for (size_t j = 0; j < st[i - 1].size() - two; ++j)
            {
                st[i].push_back(min(st[i - 1][j], st[i - 1][j + two]));
            }
            two <<= 1;
        }
        size_t m;
        unsigned int root = 0, lcaUV, lcaUR, lcaVR, temp;
        char op;
        cin >> m;
        for (size_t i = 0; i < m; ++i)
        {
            cin >> op;
            if (op == '?')
            {
                cin >> u >> v;
                --u;
                --v;
                u = index[u];
                v = index[v];
                if (u > v)
                {
                    swap(u, v);
                }
                lcaUV = min(st[log[v - u]][u], st[log[v - u]][v - (1 << log[v - u]) + 1]).second;
                temp = u;
                u = root;
                if (u > v)
                {
                    swap(u, v);
                }
                lcaUR = min(st[log[v - u]][u], st[log[v - u]][v - (1 << log[v - u]) + 1]).second;
                u = temp;
                v = root;
                if (u > v)
                {
                    swap(u, v);
                }
                lcaVR = min(st[log[v - u]][u], st[log[v - u]][v - (1 << log[v - u]) + 1]).second;
                if (depth[index[lcaVR]] > depth[index[lcaUV]])
                {
                    cout << lcaVR + 1 << endl;
                    continue;
                }
                if (depth[index[lcaUR]] > depth[index[lcaUV]])
                {
                    cout << lcaUR + 1 << endl;
                    continue;
                }
                cout << lcaUV + 1 << endl;
            }
            else
            {
                cin >> root;
                --root;
                root = index[root];
            }
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
