#include <iostream>

using namespace std;

unsigned long long d[5001][5001];

const unsigned long long MOD = 998244353;

int main()
{
    freopen("d15.out", "w", stdout);
    for (size_t i = 2; i < 5001 ; ++i)
    {
        d[1][i] = 1;
    }
    for (size_t j = 3; j < 16; ++j)
    {
        for (size_t i = 2; i < 16; ++i)
        {
            for (size_t k = 1; k < i; ++k)
            {
                d[i][j] = (d[i][j] + d[k][j - 1] * d[i - k][j]) % MOD;
            }
        }
    }
    for (size_t i = 0; i < 16; ++i)
    {
        for (size_t j = 0; j < 16; ++j)
        {
            printf("%llu, ", d[i][j]);
        }
        printf("\n");
    }
    return 0;
}
