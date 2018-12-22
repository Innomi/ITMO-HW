#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    freopen("cyclic.in", "r", stdin);
    freopen("cyclic.out", "w", stdout);
    char c;
    vector<unsigned int> z(1, 0);
    unsigned int l(0), r(0), ans(0);
    string s;
    while ((c = getchar()) >= 'a' && c <= 'z')
    {
        s += c;
    }
    s += s + '|';
    z.resize(s.length());
    for (unsigned int i = 1; i < s.length() - 1; ++i)
    {
        if (i < r)
        {
            z[i] = min(z[i - l], r - i);
        }
        while (s[z[i]] == s[i + z[i]])
        {
            ++z[i];
        }
        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }
    for (size_t i = 1; i < s.length() / 2; ++i)
    {
        if (s[z[i]] > s[i + z[i]])
        {
            ++ans;
        }
    }
    printf("%d", ++ans);
    return 0;
}
