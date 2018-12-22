#include <stdio.h>

int main()
{
    char nums[1000000] = { 0 };
    for (size_t i = 2; i * i < 1000000; ++i)
    {
        if (!nums[i])
        {
            for (size_t j = i * i; j < 1000000; j += i)
            {
                nums[j] = 1;
            }
        }
    }

    unsigned int n, a;

    scanf("%u", &n);
    
    for (size_t i = 0; i < n; ++i)
    {
        scanf("%u", &a);
        if (nums[a])
        {
            printf("NO\n");
        }
        else
        {
            printf("YES\n");
        }
    }
    return 0;
}
