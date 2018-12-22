#include <stdio.h>
#include <string.h>

#define PRIMES_AMOUNT 3401
#define BLOCK_SIZE 100000

int main()
{
    int n, x, h = 0;

    scanf("%d %d", &n, &x);
    
    char nums[BLOCK_SIZE] = { 0 };
    int primes[PRIMES_AMOUNT], cur_prime = 0;
    for (size_t i = 2; i * i < BLOCK_SIZE; ++i)
    {
        if (!nums[i])
        {
            for (size_t j = i * i; j < BLOCK_SIZE; j += i)
            {
                nums[j] = 1;
            }
        }
    }

    for (size_t i = 2; i < BLOCK_SIZE; ++i)
    {
        if (!nums[i])
        {
            if (i > n)
            {
                printf("%d\n", h);
                return 0;
            }
            h = h * x + i;
            if (i * i < 1000000000)
            {
                primes[cur_prime] = i;
                ++cur_prime;
            }
        }
    }

    size_t tmp;

    for (size_t i = 1; i < 10000; ++i)
    {
        memset(nums, 0, BLOCK_SIZE);
        for (size_t j = 0; j < PRIMES_AMOUNT; ++j)
        {
            tmp = i * BLOCK_SIZE + primes[j];
            for (size_t k = tmp - tmp % primes[j]; k < BLOCK_SIZE * (i + 1); k += primes[j])
            {
                nums[k % BLOCK_SIZE] = 1;
            }
        }
        for (size_t j = 0; j < BLOCK_SIZE; ++j)
        {
            if (j + i * BLOCK_SIZE > n)
            {
                printf("%d\n", h);
                return 0;
            }
            if (!nums[j])
            {
                h = h * x + (j + i * BLOCK_SIZE);
            }
        }
    }
    
    printf("%d\n", h);

    return 0;
}
