#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

ifstream cin("practice.in");
ofstream cout("practice.out");

int main()
{
    int n, t, r0;
    cin >> n >> t >> r0;
    vector<int> d(t + 2, r0);
    vector< vector<int> > ans(t + 2);
    vector< tuple<int, int, int, int> > mas(n + 1);
    for (size_t i = 1; i <= n; ++i)
    {
        int s, p, t;
        cin >> s >> p >> t;
        mas[i] = make_tuple(s, p, t, i);
    }
    mas[0] = make_tuple(0, 0, 0, 0);
    sort(mas.begin(), mas.end());
    for (size_t i = 1; i <= n; ++i)
    {
        int indS = get<0>(mas[i]), indP = get<1>(mas[i]), indT = get<2>(mas[i]), indI = get<3>(mas[i]);
        for (size_t j = t; j >= 1; --j)
        {
            if((int)j + indT <= t + 1 && d[j] >= indS && d[j] + indP >= d[j + indT])
            {
                d[j + indT] = d[j] + indP;
                ans[j + indT] = ans[j];
                ans[j + indT].push_back(indI);
            }
        }
    }
    cout << d[t + 1] << endl;
    for (size_t i = 0; i < ans[t + 1].size(); ++i)
    {
        cout << ans[t + 1][i] << ' ';
    }
    return 0;
}
