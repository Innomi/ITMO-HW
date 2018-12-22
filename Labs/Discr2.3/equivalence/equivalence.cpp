#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream cin("equivalence.in");
ofstream cout("equivalence.out");

int main()
{
    bool identity = true;
    bool terminals1[1001] = { 0 };
    bool terminals2[1001] = { 0 };
    unsigned int n1, m1, k1, n2, m2, k2, b, e, t;
    cin >> n1 >> m1 >> k1;
    vector< vector<unsigned int> > edges1(n1 + 1, vector<unsigned int>(26, n1));
    for (size_t i = 0; i < k1; ++i)
    {
        cin >> t;
        terminals1[t - 1] = true;
    }
    char c;
    for (size_t i = 0; i < m1; ++i)
    {
        cin >> b >> e >> c;
        edges1[b - 1][c - 'a'] = e - 1;
    }
    cin >> n2 >> m2 >> k2;
    vector< vector<unsigned int> > edges2(n2 + 1, vector<unsigned int>(26, n2));
    for (size_t i = 0; i < k2; ++i)
    {
        cin >> t;
        terminals2[t - 1] = true;
    }
    for (size_t i = 0; i < m2; ++i)
    {
        cin >> b >> e >> c;
        edges2[b - 1][c - 'a'] = e - 1;
    }
    queue< pair<unsigned int, unsigned int> > q;
    q.push(make_pair(0, 0));
    pair<unsigned int, unsigned int> cur;
    bool used1[1001] = { 0 };
    bool used2[1001] = { 0 };
    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        if (terminals1[cur.first] != terminals2[cur.second])
        {
            identity = false;
            break;
        }
        used1[cur.first] = true;
        used2[cur.second] = true;
        for (size_t i = 'a'; i < 'z'; ++i)
        {
            if (!used1[edges1[cur.first][i - 'a']] || !used2[edges2[cur.second][i - 'a']])
            {
                q.push(make_pair(edges1[cur.first][i - 'a'], edges2[cur.second][i - 'a']));
            }
        }
    }
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
