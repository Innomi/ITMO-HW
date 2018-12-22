#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector< vector<unsigned int> > edges(200000, vector<unsigned int>());
vector<unsigned int> sizeV(200000);
vector<int> prevCentroid(200000);
vector<bool> white(200000, false);
vector< unordered_map<unsigned int, unsigned int> > d(200000, unordered_map<unsigned int, unsigned int>());
vector< unordered_map< unsigned int, pair<long long unsigned int, long long unsigned int> > > subSum(200000, unordered_map< unsigned int, pair<long long unsigned int, long long unsigned int> >());
vector< vector<long long unsigned int> > sums(200000, vector<long long unsigned int>(2, 0));
vector< vector<unsigned int> > amount(200000, vector<unsigned int>(2, 0));

size_t dfs1(unsigned int p, unsigned int v)
{
    size_t res = 1;
    for (size_t i = 0; i < edges[v].size(); ++i)
    {
        if (edges[v][i] != p)
        {
            res += dfs1(v, edges[v][i]);
        }
    }
    sizeV[v] = res;
    return res;
}

long long unsigned int dfs2(unsigned int p, unsigned int v, unsigned int dist, unsigned int to)
{
    long long unsigned int res = dist;
    d[to].insert(make_pair(v, dist));
    for (size_t i = 0; i < edges[v].size(); ++i)
    {
        if (edges[v][i] != p)
        {
            res += dfs2(v, edges[v][i], dist + 1, to);
        }
    }
    return res;
}

unsigned int findCentroid(unsigned int v)
{
    dfs1(v, v);
    size_t size = sizeV[v];
    bool end = false;
    unsigned int p = v;
    while (!end)
    {
        end = true;
        for (size_t i = 0; i < edges[v].size(); ++i)
        {
            if (edges[v][i] != p && sizeV[edges[v][i]] > size / 2)
            {
                end = false;
                p = v;
                v = edges[v][i];
                break;
            }
        }
    }
    return v;
}

void build(unsigned int v, int prev)
{
    unsigned int cur = findCentroid(v);
    amount[cur][0] = sizeV[v];
    prevCentroid[cur] = prev;
    if (prev != -1)
    {
        subSum[prev].insert(make_pair(cur, make_pair(dfs2(prev, v, 1, prev), 0)));
        sums[prev][0] += subSum[prev][cur].first;
    }
    vector<unsigned int> nextStep;
    for (size_t i = 0; i < edges[cur].size(); ++i)
    {
        nextStep.push_back(edges[cur][i]);
    }
    edges[cur].clear();
    for (size_t i = 0; i < nextStep.size(); ++i)
    {
        for (auto j = edges[nextStep[i]].begin(); j != edges[nextStep[i]].end(); ++j)
        {
            if (*j == cur)
            {
                edges[nextStep[i]].erase(j);
                break;
            }
        }
        build(nextStep[i], cur);
    }
}

int main()
{
    //freopen("test.in", "r", stdin);
    size_t n, m;
    cin >> n >> m;
    unsigned int u, v;
    for (size_t i = 1; i < n; ++i)
    {
        cin >> u >> v;
        --u;
        --v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    build(n / 2, -1);
    unsigned int type, w, cur;
    for (size_t i = 0; i < m; ++i)
    {
        cin >> type >> w;
        --w;
        cur = w;
        if (type == 1)
        {
            amount[cur][white[w]]--;
            amount[cur][!white[w]]++;
            while (prevCentroid[cur] != -1)
            {
                sums[prevCentroid[cur]][white[w]] -= d[prevCentroid[cur]][w];
                sums[prevCentroid[cur]][!white[w]] += d[prevCentroid[cur]][w];
                if (white[w])
                {
                    subSum[prevCentroid[cur]][cur].first += d[prevCentroid[cur]][w];
                    subSum[prevCentroid[cur]][cur].second -= d[prevCentroid[cur]][w];
                }
                else
                {
                    subSum[prevCentroid[cur]][cur].first -= d[prevCentroid[cur]][w];
                    subSum[prevCentroid[cur]][cur].second += d[prevCentroid[cur]][w];
                }
                --amount[prevCentroid[cur]][white[w]];
                ++amount[prevCentroid[cur]][!white[w]];
                cur = prevCentroid[cur];
            }
            white[w] = !white[w];
        }
        else
        {
            long long unsigned int ans = sums[w][white[w]];
            while (prevCentroid[cur] != -1)
            {
                ans += sums[prevCentroid[cur]][white[w]] + (long long unsigned int)amount[prevCentroid[cur]][white[w]] * (long long unsigned int)d[prevCentroid[cur]][w];
                if (!white[w])
                {
                    ans -= (subSum[prevCentroid[cur]][cur].first + (long long unsigned int)amount[cur][0] * (long long unsigned int)d[prevCentroid[cur]][w]);
                }
                else
                {
                    ans -= (subSum[prevCentroid[cur]][cur].second + (long long unsigned int)amount[cur][1] * (long long unsigned int)d[prevCentroid[cur]][w]);
                }
                cur = prevCentroid[cur];
            }
            cout << ans << endl;
        }
    }
    /*
    for (size_t i = 0; i < n; ++i)
    {
        cout << sums[i][0] << ' ';
    }
    cout << endl << endl;
    for (size_t i = 0; i < n; ++i)
    {
        cout << sums[i][1] << ' ';
    }
    cout << endl << endl;
    for (size_t i = 0; i < n; ++i)
    {
        cout << amount[i][0] << ' ';
    }
    cout << endl << endl;
    for (size_t i = 0; i < n; ++i)
    {
        cout << amount[i][1] << ' ';
    }
    */
    return 0;
}
