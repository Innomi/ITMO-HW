#include <fstream>
#include <vector>
#include <queue>
#include <climits>
  
using namespace std;
  
int main()
{
    freopen("pathbgep.in", "r", stdin);
    freopen("pathbgep.out", "w", stdout);
    unsigned int n, m, cur, b, e, c;
    scanf("%u%u", &n, &m);
    vector< vector < pair<unsigned int, int> > > edges(n, vector< pair<unsigned int, int> >()); 
    vector<int> dist(n, INT_MAX);
    dist[0] = 0;
    for (size_t i = 0; i < m; ++i)
    {
        scanf("%u%u%u", &b, &e, &c);
        edges[b - 1].push_back(make_pair(e - 1, c));
        edges[e - 1].push_back(make_pair(b - 1, c));
    }
    priority_queue< pair<int, unsigned int> > q;
    q.push(make_pair(0, 0));
    while (!q.empty())
    {
        cur = q.top().second;
        q.pop();
        while (!q.empty() && q.top().first != -dist[q.top().second])
        {
            q.pop();
        }
        for (size_t i = 0; i < edges[cur].size(); ++i)
        {
            if (dist[edges[cur][i].first] > edges[cur][i].second + dist[cur])
            {
                dist[edges[cur][i].first] = edges[cur][i].second + dist[cur];
                q.push(make_pair(-dist[edges[cur][i].first], edges[cur][i].first));
            }
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        printf("%u ", dist[i]);
    }
    return 0;
}
