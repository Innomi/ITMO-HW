#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const long long INF = 1e12;

struct Edge {
    Edge(unsigned long long from, unsigned long long to, long long cap, 
    long long flow, long long price, unsigned long long rev) : 
    from(from), to(to), cap(cap), flow(flow), price(price), rev(rev) {}
    
    unsigned long long from, to;
    long long cap, flow, price;
    unsigned long long rev;
};

int main()
{
    freopen("mincost.in", "r", stdin);
    freopen("mincost.out", "w", stdout);
    
    unsigned int n, m;
    scanf("%u %u", &n, &m);
    
    vector<Edge> edges;
    vector< vector<unsigned long long> > graph(n, vector<unsigned long long>());
    
    for (size_t i = 0; i < m; ++i)
    {
        unsigned long long from, to;
        long long cap, price;
        scanf("%llu %llu %lld %lld", &from, &to, &cap, &price);
        edges.emplace_back(from - 1, to - 1, cap, 0, price, 0);
        edges.emplace_back(to - 1, from - 1, 0, 0, -price, 0);
        unsigned long long len = edges.size();
        edges[len - 1].rev = len - 2;
        edges[len - 2].rev = len - 1;
        graph[edges[len - 1].from].push_back(len - 1);
        graph[edges[len - 2].from].push_back(len - 2);
    }
    
    long long cost(0);
    
    vector<long long> d;
    vector<unsigned long long> p;
    deque<unsigned long long> q;
    vector<short> i;
    
    while (true)
    {
        d.assign(n, INF);
        p.assign(n, INF);
        i.assign(n, 0);
        d[0] = 0;
        q.push_back(0);
        
        while (!q.empty())
        {
            unsigned long long v = q.front();
            q.pop_front();
            i[v] = 1;
            for (size_t u = 0; u < graph[v].size(); ++u)
            {
                Edge & edge = edges[graph[v][u]];
                if (d[v] < INF
                && d[edge.to] > d[v] + edge.price
                && edge.flow < edge.cap)
                {
                    d[edge.to] = d[v] + edge.price;
                    p[edge.to] = graph[v][u];
                    if (i[edge.to] == 0)
                    {
                        q.push_back(edge.to);
                    }
                    else
                    {
                        if (i[edge.to] == 1)
                        {
                            q.push_front(edge.to);
                        }
                    }
                    i[edge.to] = 1;
                }
            }
        }
        
        if (d[n - 1] == INF)
        {
            break;
        }
        else
        {
            unsigned long long cur = n - 1;
            long long minF = INF;
            while (p[cur] != INF)
            {
                minF = min(minF, edges[p[cur]].cap - edges[p[cur]].flow);
                cur = edges[p[cur]].from;
            }
            cur = n - 1;
            while (p[cur] != INF)
            {
                edges[p[cur]].flow += minF;
                unsigned long long rev = edges[p[cur]].rev;
                edges[rev].flow -= minF;
                cost += minF * edges[p[cur]].price;
                cur = edges[p[cur]].from;
            }
        }
    }
    
    printf("%lld\n", cost);
    
    return 0;
}
