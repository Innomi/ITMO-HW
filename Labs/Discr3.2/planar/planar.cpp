#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>

using namespace std;

const unsigned int MNOGO = 9546254;

int main()
{
    unsigned int n, m;
    cin >> n >> m;
    vector< pair<unsigned int, unsigned int> > edges;
    vector< pair<float, float> > coords(m);
    unsigned int u, v;
    int lastFace = 2;
    vector< unordered_set<int> > facesV(n, unordered_set<int>());
    for (size_t i = 0; i < m; ++i)
    {
        cin >> u >> v;
        edges.push_back(make_pair(u - 1, v - 1));
    }
    vector<int> cycle(n);
    for (size_t i = 0; i < n; ++i)
    {
        cin >> u;
        cycle[u - 1] = i;
        facesV[i].insert(lastFace - 1);
        facesV[i].insert(-(lastFace));
    }
    vector<unsigned int> facesE(m, 2);
    list<unsigned int> notPlacedE;
    for (size_t i = 0; i < m; ++i)
    {
        if (cycle[edges[i].first] - cycle[edges[i].second] == 1)
        {
            coords[i] = make_pair((float)cycle[edges[i].second] + 0.5, 0);
            continue;
        }
        if (cycle[edges[i].second] - cycle[edges[i].first] == 1)
        {
            coords[i] = make_pair((float)cycle[edges[i].first] + 0.5, 0);
            continue;
        }
        if (abs(cycle[edges[i].second] - cycle[edges[i].first]) == (int)n - 1)
        {
            coords[i] = make_pair(((float)cycle[edges[i].first] + (float)cycle[edges[i].second]) / 2.0,
                                  ((float)cycle[edges[i].first] + (float)cycle[edges[i].second]) / 2.0);
            continue;
        }
        coords[i] = make_pair(((float)cycle[edges[i].first] + (float)cycle[edges[i].second]) / 2.0,
                              (float)abs(cycle[edges[i].first] - cycle[edges[i].second]) / 2.0);
        notPlacedE.push_back(i);
    }
    while (!notPlacedE.empty())
    {
        unsigned int minF = MNOGO;
        auto i = notPlacedE.begin();
        auto minE = i;
        while (i != notPlacedE.end() && minF != 1)
        {
            if (facesE[*i] < minF)
            {
                minF = facesE[*i];
                minE = i;
            }
            ++i;
        }
        for (auto k = facesV[cycle[edges[*minE].first]].begin(); k != facesV[cycle[edges[*minE].first]].end(); ++k)
        {
            if (facesV[cycle[edges[*minE].second]].count(*k))
            {
                int sign = *k > 0 ? 1 : -1;
                coords[*minE].second *= (float)sign;
                ++lastFace;
                for (size_t j = min(cycle[edges[*minE].second], cycle[edges[*minE].first]) + 1; j < max(cycle[edges[*minE].second], cycle[edges[*minE].first]); ++j)
                {
                    if (facesV[j].erase(*k))
                    {
                        facesV[j].insert(lastFace * sign);
                    }
                }
                facesV[cycle[edges[*minE].second]].insert(lastFace * sign);
                facesV[cycle[edges[*minE].first]].insert(lastFace * sign);
                break;
            }
        }
        notPlacedE.erase(minE);
        i = notPlacedE.begin();
        while (i != notPlacedE.end())
        {
            unsigned int curFaces(0);
            for (auto k = facesV[cycle[edges[*i].first]].begin(); k != facesV[cycle[edges[*i].first]].end(); ++k)
            {
                if (facesV[cycle[edges[*i].second]].count(*k))
                {
                    ++curFaces;
                }
            }
            facesE[*i] = curFaces;
            if (!curFaces)
            {
                cout << "NO" << endl;
                return 0;
            }
            ++i;
        }
    }
    cout << "YES" << endl;
    for (size_t i = 0; i < n; ++i)
    {
        cout << cycle[i] << " 0 ";
    }
    cout << endl;
    for (size_t i = 0; i < m; ++i)
    {
        cout << coords[i].first << " " << coords[i].second << endl;
    }
    return 0;
}
