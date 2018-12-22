#include <fstream>
#include <cmath>

using namespace std;

ifstream cin("shooter.in");
ofstream cout("shooter.out");

int main()
{
    unsigned int n, m ,k;
    double ans, averageMissChance, missChance, temp, b;
    cin >> n >> m >> k;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> temp;
        temp = 1 - temp;
        b = temp;
        for (size_t j = 1; j < m; ++j)
        {
            b *= temp;
        }
        if (i == k - 1)
        {
            missChance = b;
        }
        averageMissChance += b;
    }
    averageMissChance /= (double)n;
    ans = missChance / averageMissChance / (double)n;
    cout.precision(13);
    cout << ans;
    return 0;
}
