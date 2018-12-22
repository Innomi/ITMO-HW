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
    long long int d[18][262144], m, n, ans, price[18][18];
    for (int i = 0; i < 18; ++i)
    {
        for (int j = 0; j < 18; ++j)
        {
            price[i][j] = -1;
            if (i == j)
            {
                price[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < 262144; ++i)
    {
        for (int j = 0; j < 18; j++)
        {
            d[j][i] = INT_MAX;
        }
    }
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        d[i][0] = 0;
    }
    int a, b, w;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b >> w;
        price[a - 1][b - 1] = price[b - 1][a - 1] = w;
    }
    for (int i = 1; i < (1 << n); ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (((1 << j) & i) == (1 << j))
            {
                for (int k = 0; k < n; ++k)
                {
                    if (price[j][k] != -1)
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
        if (d[i][(1 << n) - 1] != 0)
        {
            ans = min(ans, d[i][(1 << n) - 1]);
        }
    }
    if (n == 1)
    {
        ans = 0;
    }
    if (ans == INT_MAX)
    {
        ans = -1;
    }
    cout << ans;
    return 0;
}
