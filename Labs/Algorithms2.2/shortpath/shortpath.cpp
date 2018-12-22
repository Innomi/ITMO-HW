#include <fstream>
#include <vector>
#include <climits>
 
using namespace std;
 
ifstream cin("shortpath.in");
ofstream cout("shortpath.out");
 
int main()
{
    int inDegree[100000] = { 0 };
    unsigned int n, m, s, t, b, e, curNode, beg = 0, end = 0, cur;
    vector< vector< pair<unsigned int, int> > > edges;
    int w;
    cin >> n >> m >> s >> t;
    vector<int> ans(n, 1e9 + 1);
    ans[s - 1] = 0;
    for (size_t i = 0; i < n; ++i)
    {
        vector< pair<unsigned int, int> > temp;
        edges.push_back(temp);
    }
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e >> w;
        inDegree[e - 1]++;
        edges[b - 1].push_back(make_pair(e - 1, w));
    }
    vector<unsigned int> topsort;
    vector<unsigned int> queue(n);
    for (size_t i = 0; i < n; ++i)
    {
        if (inDegree[i] == 0)
        {
            queue[end++] = i;
        }
    }
    while (beg != end)
    {
        cur = queue[beg++];
        topsort.push_back(cur);
        for (size_t i = 0; i < edges[cur].size(); ++i)
        {
            inDegree[edges[cur][i].first]--;
            if (inDegree[edges[cur][i].first] == 0)
            {
                queue[end++] = edges[cur][i].first;
            }
        }
    }
    unsigned int start;
    for (size_t i = 0; i < topsort.size(); ++i)
    {
        if (topsort[i] == s - 1)
        {
            start = i;
            break;
        }
    }
    for (size_t j = start; j < topsort.size(); ++j)
    {
        curNode = topsort[j];
        for (size_t i = 0; i < edges[curNode].size(); ++i)
        {
            if (ans[edges[curNode][i].first] > ans[curNode] + edges[curNode][i].second)
            {
                ans[edges[curNode][i].first] = ans[curNode] + edges[curNode][i].second;
            }
        }
    }
    if (ans[t - 1] > 1e8)
    {
        cout << "Unreachable";
    }
    else
    {
        cout << ans[t - 1];
    }
    return 0;
}
