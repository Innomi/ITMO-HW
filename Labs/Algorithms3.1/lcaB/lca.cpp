#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

vector< vector<unsigned int> > sons(500000, vector<unsigned int>());
vector<unsigned int> path;
vector<unsigned int> depth;
vector<unsigned int> index(500000);
unsigned int maxI = 0;

void dfs(unsigned int v, unsigned int d)
{
    index[v] = depth.size();
    if (index[v] > maxI)
    {
        maxI = index[v];
    }
    path.push_back(v);
    depth.push_back(d);
    for (size_t i = 0; i < sons[v].size(); ++i)
    {
        dfs(sons[v][i], d + 1);
        path.push_back(v);
        depth.push_back(d);
    }
    if (!sons[v].size())
    {
        path.push_back(v);
        depth.push_back(d);
    }
}

int main()
{
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
    size_t n;
    cin >> n;
    vector< pair<unsigned int, unsigned int> > get;
    unsigned int v, u;
    char c;
    for (size_t i = 0; i < n; ++i)
    {
        c = getchar();
        while (c != 'A' && c != 'G')
        {
            c = getchar();
        }
        getchar();
        getchar();
        fscanf(stdin, "%u%u", &v, &u);
        if (c == 'A')
        {
            sons[v - 1].push_back(u - 1);
        }
        else
        {
            get.push_back(make_pair(v, u));
        }
    }
    dfs(0, 0);
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
    for (size_t i = 0; i < get.size(); ++i)
    {
        v = get[i].first;
        u = get[i].second;
        v = index[v - 1];
        u = index[u - 1];
        if (v > u)
        {
            swap(v, u);
        }
        fprintf(stdout, "%u\n", min(st[log[u - v]][v], st[log[u - v]][u - (1 << log[u - v]) + 1]).second + 1);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
