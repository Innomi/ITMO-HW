#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

ifstream cin("pathbge1.in");
ofstream cout("pathbge1.out");

int main()
{
    unsigned int n, m, b, e, cur;
    bool used[30000] = { 0 };
    cin >> n >> m;
    vector< vector<unsigned int> > edges(n, vector<unsigned int>());
    vector<unsigned int> dist(n, UINT_MAX);
    dist[0] = 0;
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e;
        edges[b - 1].push_back(e - 1);
        edges[e - 1].push_back(b - 1);
    }
    queue<unsigned int> q;
    q.push(0);
    used[0] = true;
    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        for (size_t i = 0; i < edges[cur].size(); ++i)
        {
            if (!used[edges[cur][i]])
            {
                q.push(edges[cur][i]);
                used[edges[cur][i]] = true;
            }
            if (dist[edges[cur][i]] > 1 + dist[cur])
            {
                dist[edges[cur][i]] = 1 + dist[cur];
            }
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        cout << dist[i] << ' ';
    }
    return 0;
}
