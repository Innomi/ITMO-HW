#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>
#include <vector>

using namespace std;

const double EPS = 1e-8;

struct Vertex
{
    double x, y;

    Vertex(double a, double b) : x(a), y(b) {}

    bool operator<(const Vertex &v) const {
        return (x < v.x - EPS) || (abs(x - v.x) < EPS && y < v.y - EPS);
    }
};

struct Line
{
    double x1, y1, x2, y2;

    Vertex operator+(const Line &l) const
    {
        double a1 = x1 * y2 - y1 * x2;
        double a2 = l.x1 * l.y2 - l.y1 * l.x2;
        double b = (x1 - x2) * (l.y1 - l.y2) - (y1 - y2) * (l.x1 - l.x2);
        return Vertex((a1 * (l.x1 - l.x2) - a2 * (x1 - x2)) / b, (a1 * (l.y1 - l.y2) - a2 * (y1 - y2)) / b);
    }
};

void addVertex(Vertex x, vector< vector<unsigned int> > &v, map<Vertex, unsigned int> &id, vector<Vertex> &vertexes)
{
    if (!id.count(x))
    {
        id[x] = vertexes.size();
        vertexes.push_back(x);
        v.push_back(vector<unsigned int>());
    }
}

function<bool(unsigned int, unsigned int)> cmpAngle(unsigned int center, vector<Vertex> &vertexes)
{
    return [&vertexes, center] (unsigned int a, unsigned int b)->bool
    {
        return atan2(vertexes[a].y - vertexes[center].y, vertexes[a].x - vertexes[center].x) <
               atan2(vertexes[b].y - vertexes[center].y, vertexes[b].x - vertexes[center].x);
    };
}

int main()
{
    unsigned int n;
    cin >> n;
    vector<Line> lines(n);
    map<Vertex, unsigned int> id;
    vector<Vertex> vertexes;
    vector< vector<unsigned int> > edges;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> lines[i].x1 >> lines[i].y1 >> lines[i].x2 >> lines[i].y2;
    }
    for (size_t i = 0; i < n; ++i)
    {
        vector<Vertex> temp;
        for (size_t j = 0; j < n; ++j)
        {
            Vertex v(lines[i] + lines[j]);
            if (isfinite(v.x))
            {
                addVertex(v, edges, id, vertexes);
                temp.push_back(v);
            }
        }
        sort(temp.begin(), temp.end());
        if (!temp.empty())
        {
            for (size_t j = 0; j < temp.size() - 1; ++j)
            {
                unsigned int a = id[temp[j]];
                unsigned int b = id[temp[j + 1]];
                if (a != b)
                {
                    edges[a].push_back(b);
                    edges[b].push_back(a);
                }
            }
        }
    }
    for (size_t i = 0; i < edges.size(); ++i)
    {
        sort(edges[i].begin(), edges[i].end(), cmpAngle(i, vertexes));
    }

    vector< vector<bool> > used(id.size());
    vector<double> squares;
    for (size_t i = 0; i < id.size(); ++i)
    {
        used[i].resize(edges[i].size(), false);
    }
    for (size_t i = 0; i < edges.size(); ++i)
    {
        for (size_t j = 0; j < edges[i].size(); ++j)
        {
            if (!used[i][j])
            {
                used[i][j] = true;
                vector<unsigned int> face;
                unsigned int cur = edges[i][j];
                unsigned int prev = i;
                while(true)
                {
                    face.push_back(cur);
                    auto next = upper_bound(edges[cur].begin(), edges[cur].end(), prev, cmpAngle(cur, vertexes));
                    if (next == edges[cur].end())
                    {
                        next = edges[cur].begin();
                    }
                    if (used[cur][next - edges[cur].begin()])
                    {
                        break;
                    }
                    used[cur][next - edges[cur].begin()] = true;
                    prev = cur;
                    cur = *next;
                }
                double square(0);
                face.push_back(face[0]);
                for (size_t k = 0; k < face.size() - 1; ++k)
                {
                    square += (vertexes[face[k]].x * vertexes[face[k + 1]].y - vertexes[face[k]].y * vertexes[face[k + 1]].x);
                }
                squares.push_back(square / -2.0);
            }
        }
    }
    unsigned int amount = 0;
    for (size_t i = 0; i < squares.size(); ++i)
    {
        if (squares[i] > EPS)
        {
            ++amount;
        }
    }
    cout.precision(12);
    sort(squares.begin(), squares.end());
    cout << amount << endl;
    for (size_t i = squares.size() - amount; i < squares.size(); ++i)
    {
        cout << squares[i] << endl;
    }
    return 0;
}
