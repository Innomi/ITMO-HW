#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
    freopen("chvatal.in", "r", stdin);
    freopen("chvatal.out", "w", stdout);
    unsigned int n;
    char zachemPisatBezProbelov;
    unsigned int q[100];
    unsigned int d[100] = { 0 };
    cin >> n;
    vector< vector<unsigned int> > t(n, vector<unsigned int>(n));
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
            t[i][j] = (unsigned int)zachemPisatBezProbelov - 48;
            t[j][i] = t[i][j];
            d[i] += t[i][j];
        }
        d[0] += t[0][i];
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
            while (e != i && (!t[q[b % n]][q[i % n]] || !t[q[(b + 1) % n]][q[(i + 1) % n]]))
            {
                ++i;
            }
            if (e == i)
            {
                size_t k = b + 2;
                while (!t[q[b % n]][q[k % n]])
                {
                    ++k;
                }
                for (size_t j = 1; j <= ((k - b) / 2); ++j)
                {
                    swap(q[(b + j) % n], q[(k - j + 1) % n]);
                    swap(d[(b + j) % n], d[(k - j + 1) % n]);
                }
            }
            else
            {
                for (size_t k = 1; k <= ((i - b) / 2); ++k)
                {
                    swap(q[(b + k) % n], q[(i - k + 1) % n]);
                    swap(d[(b + k) % n], d[(i - k + 1) % n]);
                }
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
