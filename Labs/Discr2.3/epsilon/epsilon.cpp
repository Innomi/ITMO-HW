#include <bits/stdc++.h>

using namespace std;

inline __attribute__((always_inline)) string getString(bool &terms)
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
        if (!terms && c >= 'a' && c <= 'z')
        {
            terms = true;
        }
        ans += c;
        c = getchar();
    }
    return ans;
}

int main()
{
    freopen("epsilon.in", "r", stdin);
    freopen("epsilon.out", "w", stdout);
    string s;
    unsigned int n;
    char c;
    unordered_map< char, vector<string> > strs;
    string eps;
    cin >> n >> c;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> c >> s;
        bool terms = false;
        s = getString(terms);
        if (terms || eps.find(c) != string::npos)
        {
            continue;
        }
        if (!s.length())
        {
            eps += c;
            continue;
        }
        if (strs.find(c) == strs.end())
        {
            vector<string> temp;
            strs[c] = temp;
        }
        strs[c].push_back(s);
    }
    unsigned int size = strs.size();
    for (size_t i = 0; i < size; ++i)
    {
        for (unordered_map< char, vector<string> >::iterator j = strs.begin(); j != strs.end(); ++j)
        {
            bool isEps;
            for (size_t k = 0; k < j->second.size(); ++k)
            {
                isEps = true;
                for (size_t l = 0; l < j->second[k].length(); ++l)
                {
                    if (eps.find(j->second[k][l]) == string::npos)
                    {
                        isEps = false;
                        break;
                    }
                }
                if (isEps)
                {
                    break;
                }
            }
            if (isEps && eps.find(j->first) == string::npos)
            {
                eps += j->first;
            }
        }
    }
    sort(eps.begin(), eps.end());
    for (size_t i = 0; i < eps.length(); ++i)
    {
        cout << eps[i] << ' ';
    }
    return 0;
}
