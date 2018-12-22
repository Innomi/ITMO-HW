#include <fstream>

using namespace std;

ifstream cin("lottery.in");
ofstream cout("lottery.out");

int main()
{
    double expected, loli = 1;
    unsigned int n, m, a, b, prevCost = 0;
    cin >> n >> m;
    for (size_t i = 0; i < m; ++i)
    {
        cin >> a >> b;
        loli /= a;
        expected += loli * (double)(b - prevCost);
        prevCost = b;
    }
    cout.precision(13);
    cout << (double)n - expected;
    return 0;
}
