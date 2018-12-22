#include <bits/stdc++.h>

using namespace std;

ifstream fin("automaton.in");
ofstream fout("automaton.out");

int main()
{
    unsigned int n, m, s;
    char sc;
    fin >> n >> sc;
    s = sc - 'A';
    vector< vector< vector<unsigned int> > > edges(27, vector< vector<unsigned int> >(26, vector<unsigned int>()));
    for (size_t i = 0; i < n; ++i)
    {
        string temp;
        char b;
        fin >> b >> temp >> temp;
        if (temp.length() == 1)
        {
            edges[b - 'A'][temp[0] - 'a'].push_back(26);
        }
        else
        {
            edges[b - 'A'][temp[0] - 'a'].push_back(temp[1] - 'A');
        }
    }
    fin >> m;
    for (size_t i = 0; i < m; ++i)
    {
        string w;
        fin >> w;
        vector< vector<unsigned int> > ans(1, vector<unsigned int>(27, 0));
        ans[0][s] = 1;
        for (size_t j = 0; j < w.length(); ++j)
        {
            vector<unsigned int> temp(27, 0);
            ans.push_back(temp);
            for (size_t k = 0; k < 27; ++k)
            {
                if (ans[j][k])
                {
                    for (size_t l = 0; l < edges[k][w[j] - 'a'].size(); ++l)
                    {
                        ans[j + 1][edges[k][w[j] - 'a'][l]] = 1;
                    }
                }
            }
        }
        if (ans[w.length()][26])
        {
            fout << "yes\n";
        }
        else
        {
            fout << "no\n";
        }
    }
    return 0;
}
