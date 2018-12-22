#include <iostream>
#include <algorithm>

using namespace std;

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int n, k, m, ans, d[200000], dp[200000];
    freopen("ski.in", "r", stdin);
    freopen("ski.out", "w", stdout);
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &d[i]);
    }
    sort(d, d + m);
    dp[0] = max(0, d[0] - k);
    for (int i = 1; i < m; ++i)
    {
        if (d[i] - d[0] < k)
        {
            dp[i] = max(0, d[i] - k);
        }
        else
        {
            int t = upper_bound(d, d + i, d[i] - k) - d - 1;
            dp[i] = d[i] - k - d[t] + dp[t];
        }
    }
    ans = n - d[m - 1] + dp[m - 1];
    for (int i = m - 1; (d[i] + k > n && i >= 1); --i)
    {
        ans = max(ans, dp[i - 1] + d[i] - d[i - 1] - 1);
    }
    ans = max(ans, d[0] - 1);
    printf("%d", ans);
    return 0;
}
