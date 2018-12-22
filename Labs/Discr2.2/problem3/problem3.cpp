#include <fstream>
#include <vector>

#define MOD 1000000007

using namespace std;

ifstream cin("problem3.in");
ofstream cout("problem3.out");

short int nodes[100000], reachable[100000];
vector< vector<unsigned int> > edges;
vector< vector<unsigned int> > edges1;
unsigned int amount[100000];
bool visited[100000];
bool cycled;

void dfs(unsigned int u)
{
    nodes[u] = 1;
    for (size_t i = 0; i < edges1[u].size(); ++i)
    {
        if (nodes[edges1[u][i]] == 0)
        {
            dfs(edges1[u][i]);
        }
        else
        {
            if (nodes[edges1[u][i]] == 1 && reachable[edges1[u][i]] == 1)
            {
                cycled = true;
            }
        }
        if (cycled)
        {
            return;
        }
    }
    nodes[u] = 2;
}

void isReachable(unsigned int u)
{
    reachable[u] = 1;
    nodes[u] = 1;
    for (size_t i = 0; i < edges[u].size(); ++i)
    {
        if (nodes[edges[u][i]] == 0)
        {
            isReachable(edges[u][i]);
        }
    }
}

void isReachable1(unsigned int u)
{
    ++reachable[u];
    nodes[u] = 1;
    for (size_t i = 0; i < edges1[u].size(); ++i)
    {
        if (nodes[edges1[u][i]] == 0)
        {
            isReachable1(edges1[u][i]);
        }
    }
}

unsigned int count(unsigned int v)
{
    if (visited[v])
    {
        return amount[v];
    }
    for (size_t i = 0; i < edges[v].size(); ++i)
    {
        if (reachable[edges[v][i]] == 2)
        {
            amount[v] = (amount[v] + count(edges[v][i])) % MOD;
        }
    }
    visited[v] = true;
    return amount[v];
}

int main()
{
    unsigned int n, m, k, b, e;
    cin >> n >> m >> k;
    unsigned int accept[100000];
    for (size_t i = 0; i < k; ++i)
    {
        cin >> accept[i];
        --accept[i];
    }
    for (size_t i = 0; i < n; ++i)
    {
        vector<unsigned int> temp;
        vector<unsigned int> temp1;
        edges.push_back(temp);
        edges1.push_back(temp1);
    }
    char c;
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e >> c;
        edges1[b - 1].push_back(e - 1);
        edges[e - 1].push_back(b - 1);
    }
    for (size_t i = 0; i < k; ++i)
    {
        isReachable(accept[i]);
    }
    for (size_t i = 0; i < n; ++i)
    {
        nodes[i] = 0;
    }
    dfs(0);
    if (reachable[0] == 0)
    {
        cout << 0;
        return 0;
    }
    if (cycled)
    {
        cout << -1;
        return 0;
    }
    for (size_t i = 0; i < n; ++i)
    {
        nodes[i] = 0;
    }
    isReachable1(0);
    amount[0] = 1;
    visited[0] = true;
    unsigned int ans = 0;
    for (size_t i = 0; i < k; ++i)
    {
        ans = (ans + count(accept[i])) % MOD;
    }
    cout << ans;
    return 0;
}
