#include <fstream>
#include <vector>

using namespace std;

ifstream cin("topsort.in");
ofstream cout("topsort.out");

int main()
{
    int queue[100000] = { 0 };
    int inDegree[100000] = { 0 };
    unsigned int n, m, b, e, beg = 0, end = 0, cur;
    cin >> n >> m;
    vector< vector<unsigned int> > edges(n);
    vector<unsigned int> ans;
    for (size_t i = 0; i < n; ++i)
    {
        vector<unsigned int> a;
        edges.push_back(a);
    }
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e;
        inDegree[e - 1]++;
        edges[b - 1].push_back(e - 1);
    }
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
        ans.push_back(cur);
        for (size_t i = 0; i < edges[cur].size(); ++i)
        {
            inDegree[edges[cur][i]]--;
            if (inDegree[edges[cur][i]] == 0)
            {
                queue[end++] = edges[cur][i];
            }
        }
    }
    if (ans.size() < n)
    {
        cout << -1;
    }
    else
    {
        for (size_t i = 0; i < ans.size(); ++i)
        {
            cout << ans[i] + 1 << ' ';
        }
    }
    return 0;
}
