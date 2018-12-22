#include <fstream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

ifstream cin("points.in");
ofstream cout("points.out");


bool visited[20000] = { 0 };
bool isPoint[20000] = { 0 };
vector< vector<unsigned int> > edges;
unsigned int n, m, t = 0, rootCh, in[20000], loli[20000], b, e;
vector<unsigned int> ans;

void dfs(unsigned int u, unsigned int prev)
{
    ++t;
    in[u] = t;
    visited[u] = true;
    for (size_t i = 0; i < edges[u].size(); ++i)
    {
        if (!visited[edges[u][i]])
        {
            if (u == 0)
            {
                rootCh++;
            }
            dfs(edges[u][i], u);
            loli[u] = loli[u] > loli[edges[u][i]] ? loli[edges[u][i]] : loli[u];
        }
        else
        {
            if (prev != edges[u][i])
            {
                loli[u] = loli[u] > in[edges[u][i]] ? in[edges[u][i]] : loli[u];
            }
        }
    }
    if (loli[u] >= in[prev])
    {
        isPoint[prev] = true;
    }
}

int main()
{
    cin >> n >> m;
    for (size_t i = 0; i < n; ++i)
    {
        vector<unsigned int> temp;
        edges.push_back(temp);
        loli[i] = UINT_MAX;
    }
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e;
        edges[b - 1].push_back(e - 1);
        edges[e - 1].push_back(b - 1);
    }
    loli[0] = 0;
    dfs(0, 0);
    if (rootCh < 2)
    {
        isPoint[0] = false;
    }
    for (size_t i = 0; i < n; ++i)
    {
        if (isPoint[i])
        {
            ans.push_back(i + 1);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (size_t i = 0; i < ans.size(); ++i)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}
