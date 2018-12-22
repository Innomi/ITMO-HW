#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream cin("negcycle.in");
ofstream cout("negcycle.out");

const int INF = 1e9;

struct edge {
    unsigned int b, e;
    int c;
};

int main()
{
    unsigned int n, m = 0;
    int t, last;
    vector<edge> edges;
    cin >> n;
    vector<int> dist(n);
    vector<int> path(n, -1);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            cin >> t;
            if (t < INF)
            {
                edge temp;
                temp.b = i;
                temp.e = j;
                temp.c = t;
                ++m;
                edges.push_back(temp);
            }
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        last = -1;
        for (size_t j = 0; j < m; ++j)
        {
            if (dist[edges[j].e] > dist[edges[j].b] + edges[j].c)
            {
                dist[edges[j].e] = max (-INF, dist[edges[j].b] + edges[j].c);
                path[edges[j].e] = edges[j].b;
                last = edges[j].e;
            }
        }
    }
    if (last == -1)
    {
        cout << "NO";
    }
    else
    {
        cout << "YES\n";
        vector<unsigned int> ans;
        for (size_t i = 0; i < n; ++i)
        {
            last = path[last];
        }
        for (int i = last; ; i = path[i])
        {
            ans.push_back(i);
            if (i == last && ans.size() > 1)
            {
                break;
            }
        }
        cout << ans.size() << '\n';
        for (size_t i = ans.size(); i > 0; --i)
        {
            cout << ans[i - 1] + 1 << ' ';
        }
    }
    return 0;
}
