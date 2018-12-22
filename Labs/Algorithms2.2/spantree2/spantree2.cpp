#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

ifstream cin("spantree2.in");
ofstream cout("spantree2.out");

int getParent(vector<int> &snm, int index)
{
    while (snm[index] != index)
    {
        index = snm[index];
    }
    return index;
}

void setParent(vector<int> &snm, int value, int index)
{
    index = getParent(snm, index);
    snm[index] = value;
}

int main()
{
    unsigned int m, n, b, e, w, ans = 0;
    cin >> n >> m;
    vector< tuple<unsigned int, unsigned int, unsigned int> > edges(m);
    vector<int> snm(n);
    for (size_t i = 0; i < n; ++i)
    {
        snm[i] = i;
    }
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e >> w;
        edges[i] = make_tuple(w, b, e);
    }
    sort(edges.begin(), edges.begin() + m);
    for (size_t i = 0; i < m; ++i)
    {
        if (getParent(snm, get<1>(edges[i]) - 1) != getParent(snm, get<2>(edges[i]) - 1))
        {
            setParent(snm, get<2>(edges[i]) - 1, get<1>(edges[i]) - 1);
            ans += get<0>(edges[i]);
        }
    }
    cout << ans;
    return 0;
}
