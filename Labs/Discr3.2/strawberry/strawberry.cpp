#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

struct Vertex
{
    double x, y;

    Vertex() : x(0), y(0) {}

    Vertex(double a, double b) : x(a), y(b) {}
};

function<bool(pair<unsigned int, unsigned int>, pair<unsigned int, unsigned int>)> cmpAngle(unsigned int center, vector<Vertex> &vertexes)
{
    return [&vertexes, center] (pair<unsigned int, unsigned int> a, pair<unsigned int, unsigned int> b)->bool
    {
        return atan2(vertexes[a.first].y - vertexes[center].y, vertexes[a.first].x - vertexes[center].x) <
               atan2(vertexes[b.first].y - vertexes[center].y, vertexes[b.first].x - vertexes[center].x);
    };
}

int main()
{
    unsigned int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s;
    --t;
    vector<Vertex> vertexes;
    double x, y;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> x >> y;
        vertexes.push_back(Vertex(x, y));
    }
    vector< vector< pair<unsigned int, unsigned int> > > edges(n, vector< pair<unsigned int, unsigned int> >());
    unsigned int u, v, w;
    for (size_t i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        --u;
        --v;
        edges[u].push_back(make_pair(v, w));
        edges[v].push_back(make_pair(u, w));
    }
    for (size_t i = 0; i < edges.size(); ++i)
    {
        sort(edges[i].begin(), edges[i].end(), cmpAngle(i, vertexes));
    }

    vector< vector<bool> > used(n, vector<bool>());
    unordered_map<unsigned long long int, unsigned int> faceOfUsed;
    vector< unordered_map<unsigned int, unsigned int> > dualEdges;
    unsigned int a; //and a - 1 vertexes in dual G, which is splitted from common face for s and t
    bool commonFounded = false;
    unsigned int curFace = 1;
    for (size_t i = 0; i < n; ++i)
    {
        used[i].resize(edges[i].size(), false);
    }
    for (size_t i = 0; i < edges.size(); ++i)
    {
        for (size_t j = 0; j < edges[i].size(); ++j)
        {
            if (!used[i][j])
            {
                unsigned int posT, posS;
                bool sFounded(false), tFounded(false);
                used[i][j] = true;
                vector<unsigned int> face;
                vector<unsigned int> indexes;
                unsigned int cur = edges[i][j].first;
                unsigned int prev = i;
                while(true)
                {
                    if (!sFounded && cur == s)
                    {
                        sFounded = true;
                        posS = face.size();
                    }
                    if (!tFounded && cur == t)
                    {
                        tFounded = true;
                        posT = face.size();
                    }
                    faceOfUsed[(unsigned long long int)prev * 100000 + (unsigned long long int)cur] = curFace;
                    face.push_back(cur);
                    auto next = upper_bound(edges[cur].begin(), edges[cur].end(), make_pair(prev, 0), cmpAngle(cur, vertexes));
                    if (next == edges[cur].end())
                    {
                        next = edges[cur].begin();
                    }
                    indexes.push_back(next - edges[cur].begin());
                    if (used[cur][next - edges[cur].begin()])
                    {
                        break;
                    }
                    used[cur][next - edges[cur].begin()] = true;
                    prev = cur;
                    cur = next->first;
                }
                faceOfUsed[(unsigned long long int)cur * 100000 + (unsigned long long int)face[0]] = curFace;
                dualEdges.push_back(unordered_map<unsigned int, unsigned int>());
                face.push_back(face[0]);
                if (!sFounded || !tFounded || commonFounded)
                {
                    for (size_t k = 0; k < face.size() - 1; ++k)
                    {
                        if (faceOfUsed.count((unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]))
                        {
                            bool exists = dualEdges[faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1].count(curFace - 1);
                            if (!exists || (exists && dualEdges[faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1][curFace - 1] > edges[face[k]][indexes[k]].second))
                            {
                                dualEdges[faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1][curFace - 1] = edges[face[k]][indexes[k]].second;
                                dualEdges[curFace - 1][faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1] = edges[face[k]][indexes[k]].second;
                            }
                        }
                    }
                }
                else
                {
                    a = curFace;
                    dualEdges.push_back(unordered_map<unsigned int, unsigned int>());
                    for (size_t k = min(posS, posT); k < max(posS, posT); ++k)
                    {
                        faceOfUsed[(unsigned long long int)face[k] * 100000 + (unsigned long long int)face[k + 1]] = curFace + 1;
                    }
                    for (size_t k = 0; k < min(posS, posT); ++k)
                    {
                        if (faceOfUsed.count((unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]))
                        {
                            bool exists = dualEdges[faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1].count(curFace - 1);
                            if (!exists || (exists && dualEdges[faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1][curFace - 1] > edges[face[k]][indexes[k]].second))
                            {
                                dualEdges[faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1][curFace - 1] = edges[face[k]][indexes[k]].second;
                                dualEdges[curFace - 1][faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1] = edges[face[k]][indexes[k]].second;
                            }
                        }
                    }
                    for (size_t k = max(posS, posT); k < face.size() - 1; ++k)
                    {
                        if (faceOfUsed.count((unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]))
                        {
                            bool exists = dualEdges[faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1].count(curFace - 1);
                            if (!exists || (exists && dualEdges[faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1][curFace - 1] > edges[face[k]][indexes[k]].second))
                            {
                                dualEdges[faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1][curFace - 1] = edges[face[k]][indexes[k]].second;
                                dualEdges[curFace - 1][faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1] = edges[face[k]][indexes[k]].second;
                            }
                        }
                    }
                    ++curFace;
                    for (size_t k = min(posS, posT); k < max(posS, posT); ++k)
                    {
                        if (faceOfUsed.count((unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]))
                        {
                            bool exists = dualEdges[faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1].count(curFace - 1);
                            if (!exists || (exists && dualEdges[faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1][curFace - 1] > edges[face[k]][indexes[k]].second))
                            {
                                dualEdges[faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1][curFace - 1] = edges[face[k]][indexes[k]].second;
                                dualEdges[curFace - 1][faceOfUsed[(unsigned long long int)face[k + 1] * 100000 + (unsigned long long int)face[k]] - 1] = edges[face[k]][indexes[k]].second;
                            }
                        }
                    }
                    commonFounded = true;
                }
                ++curFace;
            }
        }
    }

    unsigned int cur;
    vector<long long int> dist(--curFace, LLONG_MAX);
    dist[a - 1] = 0;
    priority_queue< pair<long long int, unsigned int> > q;
    q.push(make_pair(0, a - 1));
    while (!q.empty())
    {
        cur = q.top().second;
        q.pop();
        while (!q.empty() && q.top().first != -dist[q.top().second])
        {
            q.pop();
        }
        for (auto i = dualEdges[cur].begin(); i != dualEdges[cur].end(); ++i)
        {
            if (dist[i->first] > i->second + dist[cur])
            {
                dist[i->first] = i->second + dist[cur];
                q.push(make_pair(-dist[i->first], i->first));
            }
        }
    }
    cout << dist[a] << endl;
/*

8 11 3 5
0 0
1 1
2 0
1 -1
3 0
4 1
4 -1
5 0
1 2 10
1 4 100
4 3 100
3 2 100
2 6 100
6 5 500
5 7 10
7 4 300
7 8 10
8 6 10
3 5 50
170

9 12 3 5
0 0
1 1
2 0
1 -1
3 0
4 1
4 -1
5 0
3 2
1 2 10
1 4 100
4 3 100
3 2 100
2 6 100
6 5 500
5 7 10
7 4 300
7 8 10
8 6 10
3 5 50
6 9 1
170

12 11 10 3
0 0
-1 -1
-3 -2
-4 -3
-2 -3
-2 -2
0 -2
-1 -3
1 -1
2 -2
1 -3
3 -3
1 2 20
2 3 15
3 4 25
3 5 25
2 6 10
2 7 5
7 8 30
1 9 10
9 10 30
10 11 5
10 12 10
10

10 10 3 9
-2 -1
-2 1
-1 0
0 1
1 0
2 1
2 0
2 -1
0 0
0 -1
1 3 5
2 3 5
3 4 10
3 10 10
4 5 100
10 5 100
5 6 25
5 7 50
5 8 25
5 9 300
20

*/
    return 0;
}
