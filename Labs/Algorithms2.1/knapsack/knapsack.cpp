#include <fstream>
#include <climits>

using namespace std;
ifstream cin("knapsack.in");
ofstream cout("knapsack.out");

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int n, m, w[1000], c[1000], d[1001][10001], ans[1000], num = 0, a = 0;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        cin >> w[i];
        d[i][0] = 0;
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> c[i];
        d[0][i] = 0;
    }
    d[0][m] = 0;
    d[n][0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (j >= w[i - 1])
            {
                d[i][j] = max(d[i - 1][j], c[i - 1] + d[i - 1][j - w[i - 1]]);
            }
            else
            {
                d[i][j] = d[i - 1][j];
            }
        }
    }
    int ind = 0, t = n;
    for (int i = 0; i <= m; ++i)
    {
        if (a < d[n][i])
        {
            a = d[n][i];
            ind = i;
        }
    }
    while (d[t][ind] != 0)
    {
        while (d[t - 1][ind] == d[t][ind])
        {
            t--;
        }
        ans[num++] = t;
        t--;
        ind -= w[t];
    }
    cout << num << endl;
    for (int i = 0; i < num; ++i)
    {
        cout << ans[i] << " ";
    }
    return 0;
}
