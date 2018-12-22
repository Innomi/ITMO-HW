#include <fstream>
#include <vector>

using namespace std;

ifstream cin("fire.in");
ofstream cout("fire.out");

enum color { black, gray, white };
color nodes[20000];
vector< vector<unsigned int> > backEdges;
vector<unsigned int> topsort;
unsigned int acc = 1;

void topsortDfs(int u)
{
    nodes[u] = gray;
    for (size_t i = 0; i < backEdges[u].size(); ++i)
    {
        if (nodes[backEdges[u][i]] == white)
        {
            topsortDfs(backEdges[u][i]);
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
    nodes[u] = black;
}

int main()
{
    unsigned int n, m, b, e;
    cin >> n >> m;
    for (size_t i = 0; i < n; ++i)
    {
        vector<unsigned int> a;
        backEdges.push_back(a);
        nodes[i] = white;
    }
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e;
        backEdges[e - 1].push_back(b - 1);
    }
    for (size_t i = 0; i < n; ++i)
    {
        if (nodes[i] == white)
        {
            topsortDfs(i);
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
    return 0;
}
