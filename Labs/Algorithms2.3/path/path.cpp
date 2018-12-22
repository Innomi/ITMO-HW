#include <fstream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

ifstream cin("path.in");
ofstream cout("path.out");

const long long int INF = 1e18 * 2 + 1;

int main()
{
    unsigned int n, m, s, b, e;
    long long int c;
    cin >> n >> m >> s;
    --s;
    long long int dist[2000];
    for (size_t i = 0; i < n; ++i)
    {
        dist[i] = INF;
    }
    dist[s] = 0;
    vector< vector< pair<unsigned int, long long int> > > edges(n, vector< pair<unsigned int, long long int> >());
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e >> c;
        edges[b - 1].push_back(make_pair(e - 1, c));
    }
    for (size_t i = 0; i < n - 1; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            for (size_t k = 0; k < edges[j].size(); ++k)
            {
                if (dist[edges[j][k].first] > dist[j] + edges[j][k].second)
                {
                    dist[edges[j][k].first] = max(-INF, dist[j] + edges[j][k].second);
                }
            }
        }
    }
    bool changed[2000] = { 0 };
    for (size_t j = 0; j < n; ++j)
    {
        for (size_t k = 0; k < edges[j].size(); ++k)
        {
            if (dist[edges[j][k].first] > dist[j] + edges[j][k].second)
            {
                dist[edges[j][k].first] = max(-INF, dist[j] + edges[j][k].second);
                changed[edges[j][k].first] = true;
            }
        }
    }
    queue<unsigned int> q;
    unsigned int cur;
    q.push(s);
    bool used[2000] = { 0 };
    used[s] = true;
    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        for (size_t i = 0; i < edges[cur].size(); ++i)
        {
            if (!used[edges[cur][i].first])
            {
                q.push(edges[cur][i].first);
                used[edges[cur][i].first] = true;
            }
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        if (changed[i] && used[i])
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        for (size_t i = 0; i < edges[cur].size(); ++i)
        {
            if (!changed[edges[cur][i].first])
            {
                q.push(edges[cur][i].first);
                changed[edges[cur][i].first] = true;
            }
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        if (!used[i])
        {
            cout << "*\n";
            continue;
        }
        if (changed[i] || dist[i] == -INF)
        {
            cout << "-\n";
            continue;
        }
        cout << dist[i] << "\n";
    }
    return 0;
}
