#include <fstream>
#include <cmath>

using namespace std;
ifstream cin("exam.in");
ofstream cout("exam.out");

int main()
{
    unsigned int n, k, ans = 0,  a, b;
    float chance;
    cin >> k >> n;
    for (size_t i = 0; i < k; ++i)
    {
        cin >> a >> b;
        ans += a * b;
    }
    chance = (float)ans / (100 * n);
    cout << round(chance * 100000) / 100000;
}
