#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>

using namespace std;

vector<bool> usedLeft;
vector< vector<unsigned int> > edges;
vector<unsigned int> toLeft;

bool tryTyan(unsigned int v)
{
    if (usedLeft[v])
    {
        return false;
    }
    usedLeft[v] = true;
    for (size_t i = 0; i < edges[v].size(); ++i)
    {
        unsigned int toRight = edges[v][i];
        if (toLeft[toRight] == UINT_MAX || tryTyan(toLeft[toRight]))
        {
            toLeft[toRight] = v;
            return true;
        }
    }
    return false;
}

int main()
{
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    unsigned int n, weight, m, edge;
    cin >> n;
    vector< pair<unsigned int, unsigned int> > leftVs;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> weight;
        leftVs.emplace_back(weight, i);
    }
    edges.resize(n, vector<unsigned int>());
    for (size_t i = 0; i < n; ++i)
    {
        cin >> m;
        for (size_t j = 0; j < m; ++j)
        {
            cin >> edge;
            edges[i].emplace_back(edge - 1);
        }
    }
    sort(leftVs.begin(), leftVs.end());
    toLeft.resize(n, UINT_MAX);
    usedLeft.resize(n);
    for (size_t i = n; i > 0; --i)
    {
        usedLeft.assign(n, false);
        tryTyan(leftVs[i - 1].second);
    }
    vector<unsigned int> ans(n, 0);
    for (size_t i = 0; i < n; ++i)
    {
        if (toLeft[i] != UINT_MAX)
        {
            ans[toLeft[i]] = i + 1;
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        cout << ans[i] << " ";
    }
    return 0;
}
