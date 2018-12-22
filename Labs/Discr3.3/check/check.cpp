#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

unsigned int bits(unsigned int n)
{
    unsigned int count = 0;
    for (; n; count++)
    {
        n &= (n - 1);
    }
    return count;
}

bool check(vector<bool> & S)
{
    for (size_t i = 0; i < S.size(); ++i)
    {
        if (S[i])
        {
            for (size_t j = 1; j < S.size(); j = j << 1)
            {
                if (!S[~j & i])
                {
                    return false;
                }
            }
        }
    }
    for (size_t i = 0; i < S.size(); ++i)
    {
        if (S[i])
        {
            for (size_t j = 0; j < S.size(); ++j)
            {
                if (S[j] && bits(i) < bits(j))
                {
                    bool res = false;
                    for (size_t k = 1; k < S.size(); k = k << 1)
                    {
                        if ((i | (k & j)) != i && S[i | (k & j)])
                        {
                            res = true;
                            break;
                        }
                    }
                    if (!res)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main()
{
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    unsigned int n, m, size, sub, elem;
    cin >> n >> m;
    vector<bool> S(1 << n, false);
    for (size_t i = 0; i < m; ++i)
    {
        cin >> size;
        sub = 0;
        for (size_t j = 0; j < size; ++j)
        {
            cin >> elem;
            sub += (1 << (elem - 1));
        }
        S[sub] = true;
    }
    cout << (m && check(S) ? "YES" : "NO");
    fclose(stdin);
    fclose(stdout);
    return 0;
}
