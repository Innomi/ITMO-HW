#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    char c;
    vector<int> prefFun(1, -1);
    vector<unsigned int> ans;
    prefFun.emplace_back(0);
    int k(0);
    string p(""), t(""), s;
    while ((c = getchar()) >= 'A' && c <= 'z')
    {
        p += c;
    }
    while ((c = getchar()) >= 'A' && c <= 'z')
    {
        t += c;
    }
    s = p + '#' + t;
    prefFun.resize(s.length() + 1);
    for (size_t i = 2; i <= s.length(); ++i)
    {
        while (k >= 0 && s[k] != s[i - 1])
        {
            k = prefFun[k];
        }
        ++k;
        prefFun[i] = k;
        if (k == (int)p.length())
        {
            ans.emplace_back(i - p.length() - p.length());
        }
    }
    cout << ans.size() << endl;
    for (size_t i = 0; i < ans.size(); ++i)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}
