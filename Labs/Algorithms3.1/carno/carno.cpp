#include <iostream>
#include <vector>
#include <cmath>
 
using namespace std;
 
vector< vector<unsigned int> > sons(200000, vector<unsigned int>());
vector<unsigned int> firstAlive(200000);
vector<unsigned int> path;
vector<unsigned int> depth;
vector<unsigned int> index(200000);
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

unsigned int jump(unsigned int v)
{
    unsigned int fa = v;
    while (firstAlive[fa] != fa)
    {
        fa = firstAlive[fa];
    }
    unsigned int temp;
    while (firstAlive[v] != fa)
    {
        temp = firstAlive[v];
        firstAlive[v] = fa;
        v = temp;
    }
    return fa;
}

int main()
{
    freopen("carno.in", "r", stdin);
    freopen("carno.out", "w", stdout);
    vector< pair<unsigned int, unsigned int> > get;
    size_t m, n = 1;
    cin >> m;
    unsigned int v, u;
    char op;
    firstAlive[0] = 0;
    for (size_t i = 0; i < m; ++i)
    {
        cin >> op;
        if (op == '+')
        {
            cin >> v;
            sons[v - 1].push_back(n);
            firstAlive[n] = n;
            ++n;
            continue;
        }
        if (op == '-')
        {
            cin >> v;
            get.push_back(make_pair(200000, v - 1));
        }
        else
        {
            cin >> u >> v;
            get.push_back(make_pair(u - 1, v - 1));
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
        if (get[i].first != 200000)
        {
            u = index[get[i].first];
            v = index[get[i].second];
            if (u > v)
            {
                swap(u, v);
            }
            cout << jump(min(st[log[v - u]][u], st[log[v - u]][v - (1 << log[v - u]) + 1]).second) + 1 << endl;
        }
        else
        {
            v = get[i].second;
            firstAlive[v] = firstAlive[path[index[v] - 1]];
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
