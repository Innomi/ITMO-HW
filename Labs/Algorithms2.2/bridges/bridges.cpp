#include <fstream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

ifstream cin("bridges.in");
ofstream cout("bridges.out");


bool visited[20000] = { 0 };
vector< vector< pair<unsigned int, unsigned int> > > edges;
unsigned int n, m, t = 0, in[20000], loli[20000], b, e, num = 1;
vector<unsigned int> ans;

void dfs(unsigned int u, unsigned int prev)
{
    ++t;
    in[u] = t;
    visited[u] = true;
    unsigned int edge;
    for (size_t i = 0; i < edges[u].size(); ++i)
    {
        if (!visited[edges[u][i].first])
        {
            dfs(edges[u][i].first, u);
            loli[u] = loli[u] > loli[edges[u][i].first] ? loli[edges[u][i].first] : loli[u];
        }
        else
        {
            if (prev != edges[u][i].first)
            {
                loli[u] = loli[u] > in[edges[u][i].first] ? in[edges[u][i].first] : loli[u];
            }
            else
            {
                edge = edges[u][i].second;
            }
        }
    }
    if (loli[u] >= in[u])
    {
        ans.push_back(edge);
    }
}

int main()
{
    cin >> n >> m;
    for (size_t i = 0; i < n; ++i)
    {
        vector< pair<unsigned int, unsigned int> > temp;
        edges.push_back(temp);
        loli[i] = UINT_MAX;
    }
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e;
        edges[b - 1].push_back(make_pair(e - 1, num));
        edges[e - 1].push_back(make_pair(b - 1, num++));
    }
    loli[0] = 0;
    dfs(0, 0);
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (size_t i = 0; i < ans.size(); ++i)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}
