#include <iostream>

using namespace std;

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);
    int x, a, y, b, l, mid, top, bot;
    scanf("%d%d%d%d%d", &x, &a, &y, &b, &l);
    int **d = new int*[x + 1];
    for (int i = 0; i <= x; ++i)
    {
        d[i] = new int[y + 1];
    }
    top = x * a + y * b;
    bot = min(a, b);
    while (top > bot)
    {
        for (int i = 0; i <= x; ++i)
        {
            for (int j = 0; j <= y; ++j)
            {
                d[i][j] = 0;
            }
        }
        mid = (bot + top + 1) / 2;
        for (int i = 0; i <= x; ++i)
        {
            for (int j = 0; j <= y; ++j)
            {
                for (int k = 0; k <= i; ++k)
                {
                    int t = max((mid - k * a + b - 1) / b, 0);
                    if (t <= j)
                    {
                        d[i][j] = max(d[i][j], d[i - k][j - t] + 1);
                    }
                }
            }
        }
        if (d[x][y] < l)
        {
            top = mid - 1;
        }
        else
        {
            bot = mid;
        }
    }
    printf("%d", bot);
    return 0;
}
