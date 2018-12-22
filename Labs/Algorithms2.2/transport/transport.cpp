#include <fstream>
#include <cmath>

using namespace std;

ifstream cin("transport.in");
ofstream cout("transport.out");

unsigned int snm[150];

int get(unsigned int node)
{
    while (snm[node] != node)
    {
        node = snm[node];
    }
    return node;
}

int main()
{
    unsigned int n, connected = 0;
    double x[150], y[150], r, a, ans, c[150][150], min;
    cin >> n;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> x[i];
        snm[i] = i;
    }
    for (size_t i = 0; i < n; ++i)
    {
        cin >> y[i];
    }
    cin >> r >> a;
    ans = n * a;
    for (size_t i = 0; i < n - 1; ++i)
    {
        c[i][i] = 0;
        for (size_t j = i + 1; j < n; ++j)
        {
            c[i][j] = r * sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
        }
    }
    for (size_t k = 0; k < n - 1; ++k)
    {
        min = 1e15;
        unsigned int loli, lolj;
        for (size_t i = 0; i < n - 1; ++i)
        {
            for (size_t j = i + 1; j < n; ++j)
            {
                if (get(i) != get(j) && c[i][j] < min)
                {
                    min = c[i][j];
                    loli = i;
                    lolj = j;
                }
            }
        }
        if (a >= min || (connected == n - 2 && 2 * a >= min))
        {
            ans = ans - a + min;
            snm[get(lolj)] = loli;
            ++connected;
        }
    }
    if (connected == n - 1)
    {
        ans -= a;
    }
    
    double ans2 = 0;
    
    for (size_t i = 0; i < n; ++i)
    {
        snm[i] = i;
    }
    
    for (size_t k = 0; k < n - 1; ++k)
    {
        min = 1e15;
        unsigned int loli, lolj;
        for (size_t i = 0; i < n - 1; ++i)
        {
            for (size_t j = i + 1; j < n; ++j)
            {
                if (get(i) != get(j) && c[i][j] < min)
                {
                    min = c[i][j];
                    loli = i;
                    lolj = j;
                }
            }
        }
        ans2 += min;
        snm[get(lolj)] = loli;
        ++connected;
    }
    
    if (ans2 < ans)
    {
        ans = ans2;
    }
    
    cout.precision(100);
    cout << ans;
    return 0;
}
