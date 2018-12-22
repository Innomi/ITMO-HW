#include <iostream>
#include <vector>

using namespace std;

vector< vector<unsigned int> > edges(200000, vector<unsigned int>());
vector<unsigned int> sizeV(200000);
vector<int> prevCentroid(200000);

size_t dfs(unsigned int p, unsigned int v)
{
    size_t res = 1;
    for (size_t i = 0; i < edges[v].size(); ++i)
    {
        if (edges[v][i] != p)
        {
            res += dfs(v, edges[v][i]);
        }
    }
    sizeV[v] = res;
    return res;
}

unsigned int findCentroid(unsigned int v)
{
    dfs(v, v);
    size_t size = sizeV[v];
    bool end = false;
    unsigned int p = v;
    while (!end)
    {
        end = true;
        for (size_t i = 0; i < edges[v].size(); ++i)
        {
            if (edges[v][i] != p && sizeV[edges[v][i]] > size / 2)
            {
                end = false;
                p = v;
                v = edges[v][i];
                break;
            }
        }
    }
    return v;
}

void build(unsigned int v, int prev)
{
    unsigned int cur = findCentroid(v);
    prevCentroid[cur] = prev;
    vector<unsigned int> nextStep;
    for (size_t i = 0; i < edges[cur].size(); ++i)
    {
        nextStep.push_back(edges[cur][i]);
    }
    edges[cur].clear();
    for (size_t i = 0; i < nextStep.size(); ++i)
    {
        for (auto j = edges[nextStep[i]].begin(); j != edges[nextStep[i]].end(); ++j)
        {
            if (*j == cur)
            {
                edges[nextStep[i]].erase(j);
                break;
            }
        }
        build(nextStep[i], cur);
    }
}

int main()
{
    size_t n;
    cin >> n;
    unsigned int u, v;
    for (size_t i = 1; i < n; ++i)
    {
        cin >> u >> v;
        --u;
        --v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    build(0, -1);
    for (size_t i = 0; i < n; ++i)
    {
        cout << prevCentroid[i] + 1 << ' ';
    }
    return 0;
}
