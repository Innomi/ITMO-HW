#include <bits/stdc++.h>

using namespace std;

bool inserted[1000] = { 0 };
list<unsigned int> mas;
set<unsigned int> in;
set<unsigned int> out;
set<unsigned int> inOut;
vector< vector<unsigned int> > t(1000, vector<unsigned int>(1000));

int main()
{
    freopen("guyaury.in", "r", stdin);
    freopen("guyaury.out", "w", stdout);
    size_t n;
    cin >> n;
    mas.push_back(0);
    inserted[0] = true;
    char zachemPisatBezProbelov;
    t[0][0] = 2;
    for (size_t i = 1; i < n; ++i)
    {
        t[i][i] = 2;
        for (size_t j = 0; j < i; ++j)
        {
            zachemPisatBezProbelov = getchar();
            while (zachemPisatBezProbelov < '0' || zachemPisatBezProbelov > '9')
            {
                zachemPisatBezProbelov = getchar();
            }
            t[i][j] = (unsigned int)zachemPisatBezProbelov - 48;
            t[j][i] = 1 ^ t[i][j];
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        if (t[0][i] == 1)
        {
            out.insert(i);
        }
        if (t[0][i] == 0)
        {
            in.insert(i);
        }
    }
    while (mas.size() < n)
    {
        if (inOut.empty())
        {
            auto k = out.begin();
            auto l = in.begin();
            while (k != out.end())
            {
                for (auto i = in.begin(); i != in.end(); ++i)
                {
                    if (t[*k][*i] == 1)
                    {
                        l = i;
                        break;
                    }
                }
                if (t[*k][*l] == 1)
                {
                    break;
                }
                ++k;
            }
            mas.push_back(*k);
            mas.push_back(*l);
            inserted[*k] = true;
            inserted[*l] = true;
            out.erase(k);
            in.erase(l);
            for (size_t j = 0; j < n; ++j)
            {
                if (!inserted[j])
                {
                    auto e = mas.end();
                    --e;
                    if (t[*e][j] == 1)
                    {
                        if (out.insert(j).second && in.count(j))
                        {
                            inOut.insert(j);
                        }
                    }
                    if (t[*e][j] == 0)
                    {
                        if (in.insert(j).second && out.count(j))
                        {
                            inOut.insert(j);
                        }
                    }
                    --e;
                    if (t[*e][j] == 1)
                    {
                        if (out.insert(j).second && in.count(j))
                        {
                            inOut.insert(j);
                        }
                    }
                    if (t[*e][j] == 0)
                    {
                        if (in.insert(j).second && out.count(j))
                        {
                            inOut.insert(j);
                        }
                    }
                }
            }
        }
        else
        {
            for (auto k = mas.begin(); k != mas.end(); ++k)
            {
                if (t[*k][*inOut.begin()] == 1)
                {
                    while (t[*k][*inOut.begin()] != 0)
                    {
                        ++k;
                        if (k == mas.end())
                        {
                            k = mas.begin();
                        }
                    }
                    mas.insert(k, *inOut.begin());
                    --k;
                    inserted[*inOut.begin()] = true;
                    in.erase(*inOut.begin());
                    out.erase(*inOut.begin());
                    inOut.erase(inOut.begin());
                    for (size_t j = 0; j < n; ++j)
                    {
                        if (!inserted[j])
                        {
                            if (t[*k][j] == 1)
                            {
                                if (out.insert(j).second && in.count(j))
                                {
                                    inOut.insert(j);
                                }
                            }
                            if (t[*k][j] == 0)
                            {
                                if (in.insert(j).second && out.count(j))
                                {
                                    inOut.insert(j);
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
    for (auto i = mas.begin(); i != mas.end(); ++i)
    {
        cout << *i + 1 << " ";
    }
    return 0;
}
