#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Edge
{
    Edge(unsigned int u, unsigned int v, unsigned long long price, unsigned int num) : u_(u), v_(v), num_(num), price_(price) {}
    
    bool operator<(const Edge & e) const {
        return price_ < e.price_;
    }
    
    unsigned int u_, v_, num_;
    unsigned long long price_;
};

unsigned int getParent(vector<unsigned int> &snm, unsigned int index)
{
    vector<unsigned int> tmp;
    while (snm[index] != index)
    {
        tmp.push_back(index);
        index = snm[index];
    }
    for (size_t i = 0; i < tmp.size(); ++i)
    {
        snm[tmp[i]] = index;
    }
    return index;
}

void setParent(vector<unsigned int> &snm, unsigned int value, unsigned int index)
{
    index = getParent(snm, index);
    snm[index] = value;
}

int main()
{
    freopen("destroy.in", "r", stdin);
    freopen("destroy.out", "w", stdout);
    unsigned int n, m, u, v;
    unsigned long long s, price;
    cin >> n >> m >> s;
    vector<Edge> edges;
    for (size_t i = 0; i < m; ++i)
    {
        cin >> u >> v >> price;
        edges.emplace_back(u - 1, v - 1, price, i + 1);
    }
    sort(edges.begin(), edges.end());
    vector<unsigned int> snm;
    unordered_set<unsigned long long> mst;
    for (size_t i = 0; i < n; ++i)
    {
        snm.emplace_back(i);
    }
    for (size_t i = m; i > 0; --i)
    {
        if (getParent(snm, edges[i - 1].u_) != getParent(snm, edges[i - 1].v_))
        {
            setParent(snm, edges[i - 1].v_, edges[i - 1].u_);
            mst.emplace(edges[i - 1].v_ * 100000 + edges[i - 1].u_);
        }
    }
    unsigned long long res(0);
    vector<unsigned int> deleted;
    for (size_t i = 0; i < m; ++i)
    {
        if (edges[i].price_ + res > s)
        {
            break;
        }
        if (!mst.count(edges[i].v_ * 100000 + edges[i].u_))
        {
            deleted.emplace_back(edges[i].num_);
            res += edges[i].price_;
        }
    }
    cout << deleted.size() << endl;
    for (size_t i = 0; i < deleted.size(); ++i)
    {
        cout << deleted[i] << " ";
    }
    return 0;
}
