#include <fstream>
#include <string>

using namespace std;

ifstream cin("palindrome.in");
ofstream cout("palindrome.out");

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    char ans[2000];
    string seq;
    int d[2002][2002] = { 0 };
    cin >> seq;
    for (int i = 1; i <= seq.length(); ++i)
    {
        d[i][i] = 1;
        //d[0][i] = 0;
        //d[i][0] = 0;
        //d[seq.length() + 1][i] = 0;
        //d[i][seq.length() + 1] = 0;
    }
    for (int i = seq.length(); i > 0; --i)
    {
        for (int j = i + 1; j <= seq.length(); ++j)
        {
            if (seq[i - 1] == seq[j - 1])
            {
                d[i][j] = d[i + 1][j - 1] + 2;
            }
            else
            {
                d[i][j] = max(d[i][j - 1], d[i + 1][j]);
            }
        }
    }
    int x = 1, y = seq.length(), n = 0;
    while (d[x][y] != 0)
    {
        while (d[x][y - 1] == d[x][y])
        {
            --y;
        }
        while (d[x + 1][y] == d[x][y])
        {
            ++x;
        }
        ans[d[1][seq.length()] - n - 1] = seq[x - 1];
        ans[n++] = seq[x - 1];
        ++x;
        --y;
    }
    cout << d[1][seq.length()] << endl;
    for (int i = 0; i < d[1][seq.length()]; ++i)
    {
        cout << ans[i];
    }
    return 0;
}
