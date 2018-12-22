#include <iostream>
#include <vector>
#include <queue>

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
    unsigned int n, m;
    scanf("%u %u", &n, &m);
    
    vector<Edge> edges;
    vector< vector<unsigned long long> > graph(n * 2 + 2, vector<unsigned long long>());
    
    unsigned long long from, to;
    long long price;

    for (size_t i = 1; i < n * 2 + 1; i += 2)
    {
        scanf("%lld", &price);
        edges.emplace_back(i, i + 1, n, 0, price, 0);
        edges.emplace_back(i + 1, i, 0, 0, -price, 0);
        unsigned long long len = edges.size();
        edges[len - 1].rev = len - 2;
        edges[len - 2].rev = len - 1;
        graph[edges[len - 1].from].emplace_back(len - 1);
        graph[edges[len - 2].from].emplace_back(len - 2);
        edges.emplace_back(0, i, 1, 0, 0, 0);
        edges.emplace_back(i, 0, 0, 0, 0, 0);
        len = edges.size();
        edges[len - 1].rev = len - 2;
        edges[len - 2].rev = len - 1;
        graph[edges[len - 1].from].emplace_back(len - 1);
        graph[edges[len - 2].from].emplace_back(len - 2);
        edges.emplace_back(i + 1, 2 * n + 1, 1, 0, 0, 0);
        edges.emplace_back(2 * n + 1, i + 1, 0, 0, 0, 0);
        len = edges.size();
        edges[len - 1].rev = len - 2;
        edges[len - 2].rev = len - 1;
        graph[edges[len - 1].from].emplace_back(len - 1);
        graph[edges[len - 2].from].emplace_back(len - 2);
        edges.emplace_back(i + 1, i, n, 0, 0, 0);
        edges.emplace_back(i, i + 1, 0, 0, 0, 0);
        len = edges.size();
        edges[len - 1].rev = len - 2;
        edges[len - 2].rev = len - 1;
        graph[edges[len - 1].from].emplace_back(len - 1);
        graph[edges[len - 2].from].emplace_back(len - 2);
    }

    for (size_t i = 0; i < m; ++i)
    {
        scanf("%llu %llu %lld", &from, &to, &price);
        edges.emplace_back(from * 2 - 1, to * 2, n, 0, price, 0);
        edges.emplace_back(to * 2, from * 2 - 1, 0, 0, -price, 0);
        unsigned long long len = edges.size();
        edges[len - 1].rev = len - 2;
        edges[len - 2].rev = len - 1;
        graph[edges[len - 1].from].push_back(len - 1);
        graph[edges[len - 2].from].push_back(len - 2);
    }
    
    long long cost(0);
    
    vector<long long> d;
    vector<unsigned long long> p;
    priority_queue< pair<long long, unsigned long long> > q;
    
    vector<long long> fi(n * 2 + 2, INF);
    fi[0] = 0;
    bool any = true;
    while (any)
    {
        any = false;
        for (size_t i = 0; i < edges.size(); ++i)
        {
            if (fi[edges[i].from] < INF 
                    && edges[i].flow < edges[i].cap
                    && fi[edges[i].to] > fi[edges[i].from] + edges[i].price)
            {
                fi[edges[i].to] = fi[edges[i].from] + edges[i].price;
                any = true;
            }
        }
    }

    unsigned long long cur;

    while (true)
    {
        d.assign(n * 2 + 2, INF);
        p.assign(n * 2 + 2, INF);
        d[0] = 0;
        
        q.push(make_pair(0, 0));
        while (!q.empty())
        {
            cur = q.top().second;
            q.pop();
            while (!q.empty() && q.top().first != -d[q.top().second])
            {
                q.pop();
            }
            for (size_t i = 0; i < graph[cur].size(); ++i)
            {
                Edge & edge = edges[graph[cur][i]];
                long long price = edge.price
                    + fi[cur] - fi[edge.to];
                if (d[cur] < INF 
                        && d[edge.to] > price + d[cur]
                        && edge.flow < edge.cap)
                {
                    d[edge.to] = price + d[cur];
                    p[edge.to] = graph[cur][i];
                    q.push(make_pair(-d[edge.to], edge.to));
                }
            }
        }
        
        if (d[n * 2 + 1] == INF)
        {
            break;
        }
        else
        {
            cur = n * 2 + 1;
            long long minF = INF;
            while (p[cur] != INF)
            {
                minF = min(minF, edges[p[cur]].cap - edges[p[cur]].flow);
                cur = edges[p[cur]].from;
            }
            cur = n * 2 + 1;
            while (p[cur] != INF)
            {
                edges[p[cur]].flow += minF;
                unsigned long long rev = edges[p[cur]].rev;
                edges[rev].flow -= minF;
                cost += minF * edges[p[cur]].price;
                cur = edges[p[cur]].from;
            }
            fi.assign(d.begin(), d.end());
        }
    }

    printf("%lld\n", cost);
    
    return 0;
}
