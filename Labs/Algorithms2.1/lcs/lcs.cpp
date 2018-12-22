#include <fstream>

using namespace std;
ifstream cin("lcs.in");
ofstream cout("lcs.out");

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int n, m, seq1[2000], seq2[2000], d[2001][2001], ans[2000];
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> seq1[i];
        d[0][i] = 0;
    }
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> seq2[i];
        d[i][0] = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (seq1[i - 1]  == seq2[j - 1])
            {
                d[j][i] = d[j - 1][i - 1] + 1;
            }
            else
            {
                d[j][i] = max(d[j - 1][i], d[j][i - 1]);
            }
        }
    }
    int x = m, y = n, num = d[m][n] - 1;
    for (int i = 0; i < d[m][n]; ++i)
    {
        while (d[x][y - 1] == d[x][y])
        {
            --y;
        }
        while (d[x - 1][y] == d[x][y])
        {
            --x;
        }
        ans[num--] = seq1[y - 1];
        --x;
        --y;
    }
    cout << d[m][n] << endl;
    for (int i = 0; i < d[m][n]; ++i)
    {
        cout << ans[i] << " ";
    }
    return 0;
}
