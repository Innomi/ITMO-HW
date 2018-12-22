#include <fstream>

using namespace std;
ifstream cin("lis.in");
ofstream cout("lis.out");

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int n, d[5000], mas[5000], ans[5000], m = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> mas[i];
        d[i] = 0;
        for (int j = 0; j < i; ++j)
        {
            if (mas[i] > mas[j])
            {
                d[i] = max(d[i], d[j]);
            }
        }
        d[i]++;
        m = d[m] < d[i] ? i : m;
    }
    int t = m;
    ans[d[m] - 1] = mas[m];
    for (int  i = m - 1; i >= 0; --i)
    {
        if ((d[m] - d[i] == 1) && (mas[m] > mas[i]))
        {
            m = i;
            ans[d[m] - 1] = mas[m];
        }
    }
    cout << d[t] << endl;
    for (int i = 0; i < d[t]; ++i)
    {
        cout << ans[i] << " ";
    }
    return 0;
}
