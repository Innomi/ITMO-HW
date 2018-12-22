#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream cin("problem1.in");
ofstream cout("problem1.out");

int main()
{
    vector< vector< pair<unsigned int, char> > > edges;
    string word;
    cin >> word;
    unsigned int n, m, k, b, e;
    cin >> n >> m >> k;
    unsigned int accept[100000];
    for (size_t i = 0; i < k; ++i)
    {
        cin >> accept[i];
        accept[i]--;
    }
    for (size_t i = 0; i < n; ++i)
    {
        vector< pair<unsigned int, char> > temp;
        edges.push_back(temp);
    }
    char c;
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e >> c;
        edges[b - 1].push_back(make_pair(e - 1, c));
    }
    bool possible = false;
    unsigned int cur = 0;
    for (size_t j = 0; j < word.length(); ++j)
    {
        for (size_t i = 0; i < edges[cur].size(); ++i)
        {
            if (edges[cur][i].second == word[j])
            {
                cur = edges[cur][i].first;
                possible = true;
                break;
            }
        }
        if (!possible)
        {
            cout << "Rejects";
            return 0;
        }
        possible = false;
    }
    for (size_t i = 0; i < k; ++i)
    {
        if (accept[i] == cur)
        {
            cout << "Accepts";
            return 0;
        }
    }
    cout << "Rejects";
    return 0;
}
