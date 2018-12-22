#include <fstream>
#include <vector>

using namespace std;
ifstream cin("isomorphism.in");
ofstream cout("isomorphism.out");

enum color { white, gray, black };
bool identity = true;
color nodes1[100000];
color nodes2[100000];
bool terminals1[100000];
bool terminals2[100000];
vector< vector< pair<unsigned int, char> > > edges1;
vector< vector< pair<unsigned int, char> > > edges2;

void check(unsigned int u, unsigned int v)
{
    if (nodes1[u] != nodes2[v] || terminals1[u] != terminals2[v])
    {
        identity = false;
        return;
    }
    if (nodes1[u] == gray)
    {
        return;
    }
    if (nodes1[u] == white)
    {        
        nodes1[u] = gray;
        nodes2[v] = gray;
        for (size_t i = 0; i < edges1[u].size(); ++i)
        {
            bool visited = false;
            for (size_t j = 0; j < edges2[v].size(); ++j)
            {
                if (edges1[u][i].second == edges2[v][j].second)
                {
                    check(edges1[u][i].first, edges2[v][j].first);
                    visited = true;
                    break;
                }
            }
            if (!visited)
            {
                identity = false;
            }
        }
        nodes1[u] = black;
        nodes2[v] = black;
    }
}

int main()
{
    unsigned int n1, m1, k1, n2, m2, k2, b, e, t;
    cin >> n1 >> m1 >> k1;
    for (size_t i = 0; i < n1; ++i)
    {
        vector< pair<unsigned int, char> > temp;
        nodes1[i] = white;
        nodes2[i] = white;
        edges1.push_back(temp);
        edges2.push_back(temp);
    }
    for (size_t i = 0; i < k1; ++i)
    {
        cin >> t;
        terminals1[t - 1] = true;
    }
    char c;
    for (size_t i = 0; i < m1; ++i)
    {
        cin >> b >> e >> c;
        edges1[b - 1].push_back(make_pair(e - 1, c));
    }
    cin >> n2 >> m2 >> k2;
    if (n2 != n1 || m2 != m1 || k2 != k1)
    {
        cout << "NO";
        return 0;
    }
    for (size_t i = 0; i < k2; ++i)
    {
        cin >> t;
        terminals2[t - 1] = true;
    }
    for (size_t i = 0; i < m2; ++i)
    {
        cin >> b >> e >> c;
        edges2[b - 1].push_back(make_pair(e - 1, c));
    }
    check(0, 0);
    if (identity)
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
    return 0;
}
