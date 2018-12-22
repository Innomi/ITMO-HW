#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("selectw.in", "r", stdin);
    freopen("selectw.out", "w", stdout);
    int n;
    scanf("%d", &n);
    vector< tuple<int, int, int, int> > d(n);
    vector< tuple<int, int, int, int> > t(n);
    vector< vector<int> > s(n);
    vector<int> order;
    for (size_t i = 0; i < n; ++i)
    {
        s[i] = vector<int>();
    }
    for (size_t i = 0; i < n; ++i)
    {
        int p, q;
        scanf("%d%d", &p, &q);
        if (q < 0)
        {
            q = 0;
        }
        t[i] = make_tuple(p, q, 0, 0);
        if (p > 0)
        {
            s[p - 1].push_back(i + 1);
        }
        else
        {
            order.push_back(i + 1);
        }
    }
    int num = 0, k;
    while (order.size() < n)
    {
        k = order[num++];
        for (size_t i = 0; i < s[k - 1].size(); ++i)
        {
            order.push_back(s[k - 1][i]);
            get<0>(t[order.back() - 1]) = num;
        }
    }
    for (size_t i = 0; i < order.size(); ++i)
    {
        d[i] = t[order[i] - 1];
    }
    for (size_t i = n - 1; i > 0; --i)
    {
        get<2>(d[i]) += get<1>(d[i]);
        get<3>(d[get<0>(d[i]) - 1]) += max(get<2>(d[i]), get<3>(d[i]));
        get<2>(d[get<0>(d[i]) - 1]) += get<3>(d[i]);
    }
    printf("%d", max(get<2>(d[0]) + get<1>(d[0]), get<3>(d[0])));
    return 0;
}
