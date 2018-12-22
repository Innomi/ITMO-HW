#include <fstream>
#include <climits>

using namespace std;
ifstream cin("salesman.in");
ofstream cout("salesman.out");

int min(int a, int b)
{
    return a < b ? a : b;
};

int main()
{
    long long int d[19][12345], m, n, ans, price[19][19] = { 0 };
    for (int i = 0; i < 12345; ++i)
    {
        for (int j = 0; j < 19; j++)
        {
            d[j][i] = INT_MAX;
        }
    }
    d[0][0] = 0;
    cin >> n >> m;
    int a, b, w;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b >> w;
        price[a - 1][b - 1] = price[b - 1][a - 1] = w;
    }
    n++;
    for (int i = 0; i < n - 1; ++i)
    {
        price[i][n - 1] = price[n - 1][i] = 1;
    }
    for (int i = 0; i < (1 << n); ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (((1 << j) & i) == (1 << j))
            {
                for (int k = 0; k < n; ++k)
                {
                    if (price[j][k] != 0)
                    {
                        d[j][i] = min(d[j][i], price[j][k] + d[k][i - (1 << j)]);
                    }
                }
            }
        }
    }
    ans = INT_MAX;
    for (int i = 0; i < n; ++i)
    {
        cout << d[i][(1 << n) - 1] << endl;
        if (d[i][(1 << n) - 1] != 0)
        {
            ans = min(ans, d[i][(1 << n) - 1]);
        }
    }
    ans -= 2;
    if (n == 1)
    {
        ans = 0;
    }
    cout << ans;
    return 0;
}
