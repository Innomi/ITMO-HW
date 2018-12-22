#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    char c;
    vector<unsigned int> z(1, 0);
    unsigned int l(0), r(0);
    string s;
    while ((c = getchar()) >= 'A' && c <= 'z')
    {
        s += c;
    }
    s += '$';
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
        cout << z[i] << ' ';
    }
    return 0;
}
