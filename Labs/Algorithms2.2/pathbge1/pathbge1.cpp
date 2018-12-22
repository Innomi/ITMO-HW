#include <fstream>
#include <vector>

using namespace std;

ifstream cin("pathbge1.in");
ofstream cout("pathbge1.out");

int main()
{
    unsigned int n, m, b, e, pos = 0, curNode;
    cin >> n >> m;
    vector< vector<unsigned int> > edges(n);
    for (size_t i = 0; i < n; ++i)
    {
        vector<unsigned int> a;
        edges.push_back(a);
    }
    vector<unsigned int> queue(n);
    vector<unsigned int> ans(n, 0);
    vector<bool> used(n, false);
    for (size_t i = 0; i <  m; ++i)
    {
        cin >> b >> e;
        edges[b - 1].push_back(e - 1);
        edges[e - 1].push_back(b - 1);
    }
    queue.push_back(0);
    used[0] = true;
    while (queue.size() - pos != 0)
    {
        curNode = queue[pos++];
        for (size_t i = 0; i < edges[curNode].size(); ++i)
        {
            if (!used[edges[curNode][i]])
            {
                used[edges[curNode][i]] = true;
                queue.push_back(edges[curNode][i]);
                ans[edges[curNode][i]] = ans[curNode] + 1;
            }
            else
            {
                if (ans[curNode] + 1 < ans[edges[curNode][i]])
                {
                    ans[edges[curNode][i]] = ans[curNode] + 1;
                }
            }
        }
    }
    for (size_t i = 0; i < ans.size(); ++i)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}
