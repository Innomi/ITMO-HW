#include <fstream>
#include <climits>

using namespace std;
ifstream cin("matrix.in");
ofstream cout("matrix.out");

int n, mas[401], rubbish, dp[401][401], s[401][401];

int min (int a, int b)
{
    return a > b ? b : a;
};

int lazyZad(int l, int r)
{
    if (dp[l][r] == -1)
    {
        if (l + 1 == r)
        {
            dp[l][r] = 0;
        }
        else
        {
            dp[l][r] = INT_MAX;
            for (int i = l + 1; i < r; ++i)
            {
                int t = dp[l][r];
                dp[l][r] = min(dp[l][r], mas[l] * mas[i] * mas[r] + lazyZad(l, i) + lazyZad(i, r));
                if (t != dp[l][r])
                {
                    s[l][r] = i;
                }
            }
        }
    }
    return dp[l][r];
};

void loveLoli(int l, int r)
{
    if (l + 1 == r)
    {
        cout << 'A';
    }
    else
    {
        cout << '(';
        loveLoli(l, s[l][r]);
        loveLoli(s[l][r], r);
        cout << ')';
    }
    return;
}

int main()
{
    for (int i = 0; i < 401; ++i)
    {
        for (int j = 0; j < 401; ++j)
        {
            dp[i][j] = -1;
            s[i][j] = 0;
        }
    }
    cin >> n;
    cin >> mas[0] >> mas[1];
    for (int i = 2; i <= n; ++i)
    {
        cin >> rubbish >> mas[i];
    }
    lazyZad(0, n);
    loveLoli(0, n);
    /*for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            cout << s[i][j] << ' ';
        }
        cout << endl;
    }*/
    return 0;
}
