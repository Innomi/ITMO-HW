#include <fstream>
#include <vector>

using namespace std;

ifstream cin("cycle.in");
ofstream cout("cycle.out");

unsigned int first;
bool cenok = false;
enum color { black, gray, white };
color nodes[100000];
vector< vector<unsigned int> > edges;
vector<unsigned int> ans;

void dfs(unsigned int u)
{
    ans.push_back(u);
    nodes[u] = gray;
    for (size_t i = 0; i < edges[u].size(); ++i)
    {
        if (nodes[edges[u][i]] == white)
        {
            dfs(edges[u][i]);
        }
        else
        {
            if (nodes[edges[u][i]] == gray)
            {
                first = edges[u][i];
                cenok = true;
            }
        }
        if (cenok)
        {
            return;
        }
    }
    nodes[u] = black;
    ans.pop_back();
}

int main()
{
    unsigned int n, m, b, e;
    cin >> n >> m;
    for (size_t i = 0; i < n; ++i)
    {
        vector<unsigned int> a;
        edges.push_back(a);
        nodes[i] = white;
    }
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e;
        edges[b - 1].push_back(e - 1);
    }
    for (size_t i = 0; i < n; ++i)
    {
        if (nodes[i] == white)
        {
            dfs(i);
        }
        if (cenok)
        {
            break;
        }
    }
    if (ans.size() > 0)
    {
        cout << "YES\n";
        for (size_t i = 0; i < ans.size(); ++i)
        {
            if (ans[i] == first)
            {
                first = i;
                break;
            }
        }
        for (size_t i = first; i < ans.size(); ++i)
        {
            cout << ans[i] + 1 << ' ';
        }
    }
    else
    {
        cout << "NO";
    }
    return 0;
}
