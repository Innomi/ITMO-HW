#include <fstream>
#include <vector>

using namespace std;

ifstream cin("cond.in");
ofstream cout("cond.out");

enum color { black, gray, white };
color nodes[20000];
vector< vector<unsigned int> > edges;
vector< vector<unsigned int> > backEdges;
vector<unsigned int> topsort;
unsigned int ans[20000];
unsigned int acc = 0, acc1 = 0;

void dfs(int u)
{
    nodes[u] = gray;
    for (size_t i = 0; i < edges[u].size(); ++i)
    {
        if (nodes[edges[u][i]] == white)
        {
            dfs(edges[u][i]);
        }
    }
    topsort.push_back(u);
    nodes[u] = black;
}

void backDfs(int u)
{
    nodes[u] = gray;
    for (size_t i = 0; i < backEdges[u].size(); ++i)
    {
        if (nodes[backEdges[u][i]] == white)
        {
            backDfs(backEdges[u][i]);
        }
    }
    ans[u] = acc;
    nodes[u] = black;
}

int main()
{
    unsigned int n, m, b, e;
    cin >> n >> m;
    for (size_t i = 0; i < n; ++i)
    {
        vector<unsigned int> a;
        edges.push_back(a);
        backEdges.push_back(a);
        nodes[i] = white;
    }
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e;
        edges[b - 1].push_back(e - 1);
        backEdges[e - 1].push_back(b - 1);
    }
    for (size_t i = 0; i < n; ++i)
    {
        if (nodes[i] == white)
        {
            dfs(i);
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        nodes[i] = white;
    }
    for (size_t i = topsort.size(); i > 0; --i)
    {
        if (nodes[topsort[i - 1]] == white)
        {
            backDfs(topsort[i - 1]);
            acc++;
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        nodes[i] = white;
    }
    vector< vector<bool> > used;
    for (size_t i = 0; i < n; ++i)
    {
        vector<bool> a(n, 0);
        used.push_back(a);
    }
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < edges[i].size(); ++j)
        {
            if (!used[ans[i]][ans[edges[i][j]]] && ans[i] != ans[edges[i][j]])
            {
                used[ans[i]][ans[edges[i][j]]] = true;
                used[ans[edges[i][j]]][ans[i]] = true;
                acc1++;
            }
        }
    }
    cout << acc << ' ' << acc1 << endl;
    return 0;
}
