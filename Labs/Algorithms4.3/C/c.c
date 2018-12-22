#include <stdio.h>
#include <stdlib.h>

#define TESTS_AMOUNT 10

unsigned long long mul(unsigned long long a, unsigned long long b, unsigned long long n)
{
    unsigned long long d = 0;
    for (size_t i = 64; i > 0; --i)
    {
        d = (d + d) % n;
        if ((b >> (i - 1)) & 1)
        {
            d = (d + a) % n;
        }
    }
    return d;
}

unsigned long long mod_exp(unsigned long long a, unsigned long long b, unsigned long long n)
{
    unsigned long long d = 1;
    for (size_t i = 64; i > 0; --i)
    {
        d = mul(d, d, n);
        if ((b >> (i - 1)) & 1)
        {
            d = mul(d, a, n);
        }
    }
    return d;
}

char witness(unsigned long long a, unsigned long long n)
{
    unsigned long long u, t;
    for (size_t i = 1; ; ++i)
    {
        if (((n - 1) >> i) & 1)
        {
            t = i;
            u = (n - 1) >> i;
            break;
        }
    }
    unsigned long long y, x = mod_exp(a, u, n);
    for (size_t i = 0; i < t; ++i)
    {
        y = mod_exp(x, 2, n);
        if (y == 1 && x != 1 && x != n - 1)
        {
            return 1;
        }
        x = y;
    }
    if (x != 1)
    {
        return 1;
    }
    return 0;
}

char miller_rabin(unsigned long long n, unsigned long long tests_amount)
{
    unsigned long long a;
    for (size_t i = 0; i < tests_amount; ++i)
    {
        a = (rand() % (n - 1)) + 1;
        if (witness(a, n))
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    unsigned int n;
    unsigned long long a;
    scanf("%u", &n);
    for (size_t i = 0; i < n; ++i)
    {
        scanf("%llu", &a);
        if (a == 1 || (a != 2 && !(a % 2)))
        {
            printf("NO\n");
            continue;
        }
        if (a == 2 || miller_rabin(a, TESTS_AMOUNT))
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}
