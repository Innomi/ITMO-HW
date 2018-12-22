#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream cin("problem2.in");
ofstream cout("problem2.out");

int main()
{
    vector< vector< pair<unsigned int, char> > > edges;
    bool statements[100][10001] = { 0 };
    string word;
    cin >> word;
    unsigned int n, m, k, b, e;
    cin >> n >> m >> k;
    unsigned int accept[100];
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
    statements[0][0] = true;
    for (size_t i = 1; i <= word.length(); ++i)
    {
        for (size_t j = 0; j < 100; ++j)
        {
            if (statements[j][i - 1])
            {
                for (size_t k = 0; k < edges[j].size(); ++k)
                {
                    if (edges[j][k].second == word[i - 1])
                    {
                        statements[edges[j][k].first][i] = true;
                    }
                }
            }
        }
    }
    for (size_t i = 0; i < k; ++i)
    {
        if (statements[accept[i]][word.length()])
        {
            cout << "Accepts";
            return 0;
        }
    }
    cout << "Rejects";
    return 0;
}

