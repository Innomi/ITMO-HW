#include <fstream>
#include <vector>

using namespace std;

ifstream cin("hamiltonian.in");
ofstream cout("hamiltonian.out");

int main()
{
    unsigned int queue[100000] = { 0 };
    unsigned int inDegree[100000] = { 0 };
    unsigned int n, m, b, e, beg = 0, end = 0, cur;
    cin >> n >> m;
    vector< vector<unsigned int> > edges(n);
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
    if (topsort.size() < n)
    {
        cout << "NO";
        return 0;
    }
    bool path;
    for (size_t i = 0; i < topsort.size() - 1; ++i)
    {
        path = false;
        for (size_t j = 0; j < edges[topsort[i]].size(); ++j)
        {
            if (edges[topsort[i]][j] == topsort[i + 1])
            {
                path = true;
                break;
            }
        }
        if (!path)
        {
            break;
        }
    }
    if (path)
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
    return 0;
}
