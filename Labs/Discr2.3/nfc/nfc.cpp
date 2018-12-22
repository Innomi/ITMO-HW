#include <bits/stdc++.h>

using namespace std;

const unsigned long long int MOD = 1e9 + 7;

int main()
{
    freopen("nfc.in", "r", stdin);
    freopen("nfc.out", "w", stdout);
    string s;
    unsigned int n, start;
    char c;
    vector< vector<string> > strs(26, vector<string>());
    cin >> n >> c;
    start = c - 'A';
    for (size_t i = 0; i < n; ++i)
    {
        cin >> c >> s >> s;
        strs[c - 'A'].push_back(s);
    }
    cin >> s;
    unsigned long long int d[26][100][100] = { 0 };
    for (size_t i = 0; i < 26; ++i)
    {
        for (size_t j = 0; j < strs[i].size(); ++j)
        {
            if (strs[i][j].length() == 1)
            {
                for (size_t k = 0; k < s.length(); ++k)
                {
                    if (s[k] == strs[i][j][0])
                    {
                        d[i][k][k] += 1;
                    }
                }
            }
        }
    }
    for (size_t k = 1; k < s.length(); ++k)
    {
        for (size_t i = 0; i < 26; ++i)
        {
            for (size_t l = 0; l < s.length() - k; ++l)
            {
                for (size_t j = 0; j < strs[i].size(); ++j)
                {
                    if (strs[i][j].length() == 2)
                    {
                        for (size_t m = l; m < l + k; ++m)
                        {
                            d[i][l][l + k] = (d[i][l][l + k] + d[strs[i][j][0] - 'A'][l][m] * d[strs[i][j][1] - 'A'][m + 1][l + k]) % MOD;
                        }
                    }
                }
            }
        }
    }
    cout << d[start][0][s.length() - 1];
    return 0;
}
