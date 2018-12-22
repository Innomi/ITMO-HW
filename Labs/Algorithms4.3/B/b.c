#include <stdio.h>

int main()
{
    char nums[1000] = { 0 };
    unsigned int primes[168], cur_num = 0;
    for (size_t i = 2; i * i < 1000; ++i)
    {
        if (!nums[i])
        {
            for (size_t j = i * i; j < 1000; j += i)
            {
                nums[j] = 1;
            }
        }
    }

    for (size_t i = 2; i < 1000; ++i)
    {
        if (!nums[i])
        {
            primes[cur_num] = i;
            ++cur_num;
        }
    }

    unsigned int n, a, t;

    scanf("%u", &n);

    for (size_t i = 0; i < n; ++i)
    {
        scanf("%u", &a);
        t = a;
        for (size_t j = 0; j < 168 && primes[j] * primes[j] <= a; ++j)
        {
            while (!(t % primes[j]))
            {
                t /= primes[j];
                printf("%u ", primes[j]);
            }
        }
        if (t != 1)
        {
            printf("%u", t);
        }
        printf("\n");
    }
    return 0;
}
