#include <fstream>
#include <vector>

using namespace std;

ifstream cin("game.in");
ofstream cout("game.out");

int main()
{
    unsigned int queue[100000] = { 0 };
    unsigned int inDegree[100000] = { 0 };
    unsigned int n, m, b, e, beg = 0, end = 0, cur, s;
    cin >> n >> m >> s;
    vector< vector<unsigned int> > edges(n);
    vector< vector<unsigned int> > backEdges(n);
    vector<unsigned int> topsort;
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
        backEdges[e - 1].push_back(b - 1);
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
        topsort.push_back(cur);
        for (size_t i = 0; i < edges[cur].size(); ++i)
        {
            inDegree[edges[cur][i]]--;
            if (inDegree[edges[cur][i]] == 0)
            {
                queue[end++] = edges[cur][i];
            }
        }
    }
    unsigned int d[100000] = { 0 };
    for (size_t i = topsort.size(); i > 0; --i)
    {
        if (d[topsort[i - 1]] == 0)
        {
            d[topsort[i - 1]] = 2;
        }
        for (size_t j = 0; j < backEdges[topsort[i - 1]].size(); ++j)
        {
            if (d[topsort[i - 1]] == 1)
            {
                if (d[backEdges[topsort[i - 1]][j]] == 0)
                {
                    d[backEdges[topsort[i - 1]][j]] = 2;
                }
            }
            if (d[topsort[i - 1]] == 2)
            {
                d[backEdges[topsort[i - 1]][j]] = 1;
            }
        }
    }
    if (d[s - 1] == 1)
    {
        cout << "First player wins";
    }
    else
    {
        cout << "Second player wins";
    }
    return 0;
}
