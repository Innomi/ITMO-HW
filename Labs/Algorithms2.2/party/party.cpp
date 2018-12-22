#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

unsigned int n, m, b, e, acc = 0;
bool ans[1000];
unsigned int strong[2000];
vector<unsigned int> topsort;
vector< vector<unsigned int> > edges;
vector< vector<unsigned int> > backEdges;
bool visited[2000];

void dfs(unsigned int u)
{
    visited[u] = true;
    for (size_t i = 0; i < edges[u].size(); ++i)
    {
        if (!visited[edges[u][i]])
        {
            dfs(edges[u][i]);
        }
    }
    topsort.push_back(u);
}

void backDfs(int u)
{
    visited[u] = false;
    for (size_t i = 0; i < backEdges[u].size(); ++i)
    {
        if (visited[backEdges[u][i]])
        {
            backDfs(backEdges[u][i]);
        }
    }
    strong[u] = acc;
}

int main()
{
    map<string, int> friends;
    map<int, string> names;
    string rubish;
    cin >> n >> m;
    for (size_t i = 0; i < n * 2; ++i)
    {
        vector<unsigned int> temp;
        edges.push_back(temp);
        backEdges.push_back(temp);
    }
    for (size_t i = 0; i < n; ++i)
    {
        cin >> rubish;
        names[i] = rubish;
        friends['+' + rubish] = i;
        friends['-' + rubish] = i + n;
    }
    for (size_t i = 0; i < m; ++i)
    {
        cin >> rubish;
        b = friends.find(rubish)->second;
        cin >> rubish >> rubish;
        e = friends.find(rubish)->second;
        edges[b].push_back(e);
        backEdges[e].push_back(b);
        b = (b + n) % (2 * n);
        e = (e + n) % (2 * n);
        edges[e].push_back(b);
        backEdges[b].push_back(e);
    }
    for (size_t i = 0; i < 2 * n; ++i)
    {
        if (!visited[i])
        {
            dfs(i);
        }
    }
    for (size_t i = 2 * n; i > 0; --i)
    {
        if (visited[topsort[i - 1]])
        {
            backDfs(topsort[i - 1]);
            acc++;
        }
    }
    acc = 0;
    for (size_t i = 0; i < n; ++i)
    {
        if (strong[i] > strong[i + n])
        {
            acc++;
            ans[i] = true;
        }
        if (strong[i] == strong[i + n])
        {
            cout << -1;
            return 0;
        }
    }
    cout << acc << '\n';
    for (size_t i = 0; i < n; ++i)
    {
        if (ans[i])
        {
            cout << names[i] << '\n';
        }
    }
    return 0;
}
