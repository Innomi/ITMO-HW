#include <stdio.h>

int main()
{
    unsigned long long a, b, n, m, tmp;

    scanf("%llu %llu %llu %llu", &a, &b, &n, &m);

    if (n < m)
    {
        tmp = n;
        n = m;
        m = tmp;
        tmp = a;
        a = b;
        b = tmp;
    }

    for (size_t i = 0; i < m; ++i)
    {
        if ((i * n + a) % m == b)
        {
            printf("%llu\n", i * n + a);
        }
    }

    return 0;
}
