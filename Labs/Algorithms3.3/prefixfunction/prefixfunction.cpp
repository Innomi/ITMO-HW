#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    char c;
    vector<int> prefFun(1, -1);
    prefFun.emplace_back(0);
    int k(0);
    string s;
    while ((c = getchar()) >= 'A' && c <= 'z')
    {
        s += c;
    }
    prefFun.resize(s.length() + 1);
    cout << 0 << ' ';
    for (size_t i = 2; i <= s.length(); ++i)
    {
        while (k >= 0 && s[k] != s[i - 1])
        {
            k = prefFun[k];
        }
        ++k;
        prefFun[i] = k;
        cout << k << ' ';
    }
    return 0;
}
