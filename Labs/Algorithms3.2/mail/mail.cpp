#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

const unsigned int N = 50001;

vector< vector<unsigned int> > edges(N, vector<unsigned int>());
vector<unsigned int> depth(N);
vector<unsigned int> parent(N);
vector<unsigned int> path(N);
vector<bool> isHeavy(N, false);
vector<unsigned int> weight(N, 0);
vector<unsigned int> height(N);

class SegmentTree
{
public:
    SegmentTree(vector<unsigned int> v)
    {
        size_ = v.size();
        unsigned int deg(1);
        for (size_t i = 0; i < size_; ++i)
        {
            links_.insert(make_pair(v[i], i));
        }
        top_ = v[size_ - 1];
        while (size_ > 1)
        {
            size_ >>= 1;
            ++deg;
        }
        size_ <<= deg;
        tree_.resize(size_ + size_ - 1, 0);
        for (size_t i = 0; i < v.size(); ++i)
        {
            tree_[size_ - 1 + i] = height[v[i]];
        }
        for (size_t i = size_ - 1; i > 0; --i)
        {
            tree_[i - 1] = max(tree_[(i - 1) * 2 + 1], tree_[(i - 1) * 2 + 2]);
        }
    }
    
    unsigned int query(unsigned int l, unsigned int r)
    {
        return queryImpl(0, 0, size_, (*links_.find(l)).second, (*links_.find(r)).second);
    }
    
    void change(unsigned int v, unsigned int h)
    {
        unsigned int cur = size_ - 1 + (*links_.find(v)).second;
        tree_[cur] = h;
        while (cur != 0)
        {
            --cur;
            cur >>= 1;
            tree_[cur] = max(tree_[cur * 2 + 1], tree_[cur * 2 + 2]);
        }
    }
    
    unsigned int top()
    {
        return top_;
    }
   
private:
    unsigned int queryImpl(unsigned int cur, unsigned int curL, unsigned int curR, unsigned int l, unsigned int r)
    {
        if (curL >= r || curR <= l)
        {
            return 0;
        }
        if (curL >= l && curR <= r)
        {
            return tree_[cur];
        }
        return max(queryImpl(cur * 2 + 1, curL, curL + (curR - curL) / 2, l, r), queryImpl(cur * 2 + 2, curL + (curR - curL) / 2, curR, l, r));
    }
    
private:
    vector<unsigned int> tree_;
    unordered_map<unsigned int, unsigned int> links_;
    unsigned int size_;
    unsigned int top_;
};

vector<SegmentTree> st;

unsigned int dfs(unsigned int v, unsigned int p, unsigned int _depth)
{
    depth[v] = _depth;
    parent[v] = p;
    unsigned int maxWeight(0), heavy, weightSub;
    for (size_t i = 0; i < edges[v].size(); ++i)
    {
        if (edges[v][i] != p)
        {
            weightSub = dfs(edges[v][i], v, _depth + 1);
            weight[v] += weightSub;
            if (maxWeight < weightSub)
            {
                maxWeight = weightSub;
                heavy = edges[v][i];
            }
        }
    }
    if (edges[v].size() > 1 || _depth == 0)
    {
        isHeavy[heavy] = true;
    }
    ++weight[v];
    return weight[v];
}

void build()
{
    dfs(0, 0, 0);
    for (size_t i = 1; i < edges.size(); ++i)
    {
        if (edges[i].size() == 1)
        {
            unsigned int cur = i;
            vector<unsigned int> v;
            while (isHeavy[cur])
            {
                v.push_back(cur);
                path[cur] = st.size();
                cur = parent[cur];
            }
            path[cur] = st.size();
            v.push_back(cur);
            if (cur != 0)
            {
                cur = parent[cur];
                v.push_back(cur);
            }
            st.push_back(SegmentTree(move(v)));
        }
    }
    path[0] = path[1];
}

unsigned int lca(unsigned int u, unsigned int v)
{
    if (path[u] == path[v])
    {
        if (depth[u] < depth[v])
        {
            return u;
        }
        else
        {
            return v;
        }
    }
    if (depth[st[path[u]].top()] > depth[st[path[v]].top()])
    {
        return lca(st[path[u]].top(), v);
    }
    return lca(u, st[path[v]].top());
}

unsigned int query(unsigned int u, unsigned int v)
{
    unsigned int res(0);
    unsigned int _lca = lca(u, v);
    unsigned int _top = st[path[u]].top();
    if (path[u] != path[v])
    {
        while (path[u] != path[_lca])
        {
            res = max(res, st[path[u]].query(u, _top));
            u = _top;
            _top = st[path[u]].top();
        }
    }
    if (path[u] != path[v])
    {
        _top = st[path[v]].top();
        while (path[v] != path[_lca])
        {
            res = max(res, st[path[v]].query(v, _top));
            v = _top;
            _top = st[path[v]].top();
        }
    }
    res = max(res, st[path[_lca]].query(depth[u] > depth[v] ? u : v, depth[u] < depth[v] ? u : v));
    res = max(height[_lca], res);
    return res;
}

void change(unsigned int v, unsigned int h)
{
    st[path[v]].change(v, h);
}

int main()
{
    freopen("mail.in", "r", stdin);
    freopen("mail.out", "w", stdout);
    size_t n, m;
    cin >> n;
    for (size_t i = 1; i <= n; ++i)
    {
        cin >> height[i];
    }
    height[0] = 0;
    unsigned int u, v;
    char type;
    for (size_t i = 1; i < n; ++i)
    {
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    edges[0].push_back(1);
    edges[1].push_back(0);
    build();
    cin >> m;
    for (size_t i = 0; i < m; ++i)
    {
        cin >> type >> u >> v;
        if (type == '?')
        {
            cout << query(u, v) << endl;
        }
        else
        {
            change(u, v);
            height[u] = v;
        }
    }
    return 0;
}
