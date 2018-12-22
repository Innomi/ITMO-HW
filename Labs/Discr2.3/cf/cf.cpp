#include <bits/stdc++.h>

/*          __________-------____                 ____-------__________
          \------____-------___--__---------__--___-------____------/
           \//////// / / / / / \   _^-----^_   / \ \ \ \ \ \\\\\\\\/
             \////-/-/------/_/_| /___   ___\ |_\_\------\-\-\\\\/
               --//// / /  /  //|| (O)\ /(O) ||\\  \  \ \ \\\\--
                    ---__/  // /| \_  /V\  _/ |\ \\  \__---
                         -//  / /\_ ------- _/\ \  \\-
                           \_/_/ /\---------/\ \_\_/
                               ----\   |   /----
                                    | -|- |
                                   /   |   \
             _                     ---- \___|
   ___      | |
  /   \     |_|
  | |_|    / /|
  | |\ \/\/ / |
  | | \    /| |____
  \___/\/\/ \_____/
*/

using namespace std;

inline __attribute__((always_inline)) string getString()
{
    register char c = getchar();
    while (c == ' ')
    {
        c = getchar();
    }
    string ans;
    if (c == '\n')
    {
        return ans;
    }
    while (c != '\n' && c != ' ')
    {
        ans += c;
        c = getchar();
    }
    return ans;
}

int conv(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return -(c - 'a') - 2;
    }
    else
    {
        return c - 'A';
    }
}

short int d[500][110][110];
vector< vector< pair<int, int> > > rules;
string s;

short int CYK_Modified(unsigned int st, unsigned int b, unsigned int e)
{
    if (d[st][b][e] != -1)
    {
        return d[st][b][e];
    }
    d[st][b][e] = 0;
    for (size_t i = 0; i < rules[st].size(); ++i)
    {
        if (rules[st][i].first < -1 && rules[st][i].second == -1 && s[b] == -(rules[st][i].first + 2) + 'a' && b + 1 == e)
        {
            d[st][b][e] = 1;
        }
        if (rules[st][i].first >= 0 && rules[st][i].second == -1)
        {
            d[st][b][e] |= CYK_Modified(rules[st][i].first, b, e);
        }
        if (rules[st][i].first < -1 && rules[st][i].second < -1 && e - b == 2 && (-(rules[st][i].first + 2) + 'a') == s[b] && (-(rules[st][i].second + 2) + 'a') == s[e - 1])
        {
            d[st][b][e] = 1;
        }
        if (rules[st][i].first < -1 && rules[st][i].second >= 0 && (-(rules[st][i].first + 2) + 'a') == s[b])
        {
            d[st][b][e] |= CYK_Modified(rules[st][i].second, b + 1, e);
        }
        if (rules[st][i].first >= 0 && rules[st][i].second < -1 && (-(rules[st][i].second + 2) + 'a') == s[e - 1])
        {
            d[st][b][e] |= CYK_Modified(rules[st][i].first, b, e - 1);
        }
        if (e - b == 0 && rules[st][i].first == -1)
        {
            d[st][b][e] = 1;
        }
        if (rules[st][i].first >= 0 && rules[st][i].second >= 0)
        {
            for (size_t j = b; j <= e; ++j)
            {
                d[st][b][e] |= (CYK_Modified(rules[st][i].first, b, j) & CYK_Modified(rules[st][i].second, j, e));
            }
        }
        if (d[st][b][e])
        {
            return d[st][b][e];
        }
    }
    return d[st][b][e];
}

int main()
{
    freopen("cf.in", "r", stdin);
    freopen("cf.out", "w", stdout);
    unsigned int n, start;
    char c;
    vector< vector<string> > strs(26, vector<string>());
    for (size_t i = 0; i < 500; ++i)
    {
        vector< pair<int, int> > temp;
        rules.push_back(temp);
    }
    cin >> n >> c;
    start = c - 'A';
    for (size_t i = 0; i < n; ++i)
    {
        cin >> c >> s;
        s = getString();
        strs[c - 'A'].push_back(s);
    }
    cin >> s;
    unsigned int curNotT = 26;
    for (size_t i = 0; i < 26; ++i)
    {
        for (size_t j = 0; j < strs[i].size(); ++j)
        {
            unsigned int cur = i;
            for (int k = 0; k < (int)strs[i][j].size() - 2; ++k)
            {
                rules[i].push_back(make_pair(conv(strs[i][j][k]), curNotT));
                cur = curNotT;
                ++curNotT;
            }
            if (strs[i][j].size() >= 2)
            {
                rules[cur].push_back(make_pair(conv(strs[i][j][strs[i][j].length() - 2]), conv(strs[i][j][strs[i][j].length() - 1])));
            }
            else
            {
                if (strs[i][j].size() == 1)
                {
                    rules[cur].push_back(make_pair(conv(strs[i][j][strs[i][j].length() - 1]), -1));
                }
                else
                {
                    rules[cur].push_back(make_pair(-1, -1));
                }
            }
        }
    }
    for (size_t i = 0; i < 500; ++i)
    {
        for (size_t j = 0; j < 110; ++j)
        {
            for (size_t k = 0; k < 110; ++k)
            {
                d[i][j][k] = -1;
            }
        }
    }
    if (CYK_Modified(start, 0, s.length()))
    {
        cout << "yes";
    }
    else
    {
        cout << "no";
    }
    return 0;
}
