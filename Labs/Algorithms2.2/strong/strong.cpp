#include <fstream>
#include <vector>

using namespace std;

ifstream cin("strong.in");
ofstream cout("strong.out");

enum color { black, gray, white };
color nodes[20000];
unsigned int ans[20000];
vector< vector<unsigned int> > edges;
vector< vector<unsigned int> > backEdges;
vector<unsigned int> topsort;
unsigned int acc = 1;

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
    cout << acc - 1 << endl;
    for (size_t i = 0; i < n; ++i)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}
