#include <fstream>
#include <vector>
#include <climits>

using namespace std;

int main()
{
    freopen("pathmgep.in", "r", stdin);
    freopen("pathmgep.out", "w", stdout);
    unsigned long long int n, s, f, cur, ind, min;
    bool used[2000] = { 0 };
    scanf("%llu%llu%llu", &n, &s, &f);
    --s;
    --f;
    vector< vector<long long int> > table(n, vector<long long int>(n));
    vector<unsigned long long int> dist(n, ULLONG_MAX);
    dist[s] = 0;
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            scanf("%lld", &table[i][j]);
        }
    }
    for (size_t l = 0; l < n; ++l)
    {
        min = ULLONG_MAX;
        for (size_t i = 0; i < n; ++i)
        {
            if (!used[i] && min > dist[i])
            {
                min = dist[i];
                ind = i;
            }
        }
        if (min == ULLONG_MAX)
        {
            break;
        }
        cur = ind;
        for (size_t i = 0; i < n; ++i)
        {
            if (table[cur][i] > -1)
            {
                if (dist[i] > table[cur][i] + min)
                {
                    dist[i] = table[cur][i] + min;
                }
            }
        }
        used[cur] = true;
    }
    if (dist[f] == ULLONG_MAX)
    {
        printf("-1");
        return 0;
    }
    printf("%llu", dist[f]);
    return 0;
}
