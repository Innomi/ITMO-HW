#include <fstream>
#include <string>

using namespace std;
ifstream cin("levenshtein.in");
ofstream cout("levenshtein.out");

int min(int a, int b, int c)
{
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int main()
{
    int **d = new int * [5001];
    for (int i = 0; i < 5001; ++i)
    {
        d[i] = new int[5001];
    }
    string s1, s2;
    cin >> s1;
    cin >> s2;
    for (int i = 0; i <= s1.length(); ++i)
    {
        d[i][0] = i;
    }
    for (int i = 0; i <= s2.length(); ++i)
    {
        d[0][i] = i;
    }
    for (int i = 1;i <= s1.length(); ++i)
    {
        for (int j = 1; j <= s2.length(); ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                d[i][j] = d[i - 1][j - 1];
            }
            else
            {
                d[i][j] = min(d[i - 1][j - 1], d[i - 1][j], d[i][j - 1]) + 1;
            }
        }
    }
    cout << d[s1.length()][s2.length()];
    return 0;
}
