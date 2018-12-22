#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector< vector<unsigned int> > sons(100000, vector<unsigned int>());
vector<unsigned int> path;
vector<unsigned int> depth;
vector<unsigned int> index(100000);
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
    freopen("lca_rmq.in", "r", stdin);
    freopen("lca_rmq.out", "w", stdout);
    size_t n, m;
    cin >> n >> m;
    unsigned int v;
    for (size_t i = 1; i < n; ++i)
    {
        cin >> v;
        sons[v].push_back(i);
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
    unsigned long long int u, w, x, y, z, ans = 0, sum = 0, iu, iw;
    cin >> u >> w >> x >> y >> z;
    for (size_t i = 0; i < m; ++i)
    {
        iu = index[(u + ans) % n];
        iw = index[w];
        if (iu > iw)
        {
            swap(iu, iw);
        }
        ans = min(st[log[iw - iu]][iu], st[log[iw - iu]][iw - (1 << log[iw - iu]) + 1]).second;
        sum += ans;
        u = (u * x + w * y + z) % n;
        w = (w * x + u * y + z) % n;
    }
    cout << sum;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
