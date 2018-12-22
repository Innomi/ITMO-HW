#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("fullham.in", "r", stdin);
    freopen("fullham.out", "w", stdout);
    size_t n;
    char zachemPisatBezProbelov;
    int q[4000];
    cin >> n;
    vector< vector<int> > t(n, vector<int>(n));
    t[0][0] = 0;
    for (size_t i = 1; i < n; ++i)
    {
        t[i][i] = 0;
        for (size_t j = 0; j < i; ++j)
        {
            zachemPisatBezProbelov = getchar();
            while (zachemPisatBezProbelov < '0' || zachemPisatBezProbelov > '9')
            {
                zachemPisatBezProbelov = getchar();
            }
            t[i][j] = (int)zachemPisatBezProbelov - 48;
            t[j][i] = t[i][j];
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        q[i] = i;
    }
    size_t b = 0;
    size_t e = n - 1;
    for (size_t s = 0; s < n * (n - 1); ++s)
    {
        if (!t[q[b % n]][q[(b + 1) % n]])
        {
            size_t i = b + 2;
            while (!t[q[b % n]][q[i % n]] || !t[q[(b + 1) % n]][q[(i + 1) % n]])
            {
                ++i;
            }
            for (size_t k = 1; k <= ((i - b) / 2); ++k)
            {
                swap(q[(b + k) % n], q[(i - k + 1) % n]);
            }
        }
        ++e;
        ++b;
    }
    for (size_t i = b; i <= e; ++i)
    {
        cout << q[i % n] + 1 << ' ';
    }
    return 0;
}
