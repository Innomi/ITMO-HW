#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comparator(pair<unsigned long long, unsigned long long> & a, pair<unsigned long long, unsigned long long> & b)
{
    return a.first > b.first;
}

int main()
{
    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);
    unsigned long long n, d, w, res(0), t;
    cin >> n;
    vector< pair<unsigned long long, unsigned long long> > activities;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> d >> w;
        if (d == 0)
        {
            res += w;
            continue;
        }
        activities.emplace_back(w, min(d, n));
    }
    sort(activities.begin(), activities.end(), comparator);
    vector<bool> times(n, false);
    vector<unsigned int> jumps;
    jumps.emplace_back(0);
    for (size_t i = 1; i < n; ++i)
    {
        jumps.emplace_back(i - 1);
    }
    for (size_t i = 0; i < activities.size(); ++i)
    {
        t = activities[i].second - 1;
        while (times[t])
        {
            if (t == 0)
            {
                res += activities[i].first;
                break;
            }
            t = jumps[t];
        }
        if (t > 0)
        {
            jumps[activities[i].second - 1] = t - 1;
        }
        else
        {
            jumps[activities[i].second - 1] = 0;
        }
        times[t] = true;
    }
    cout << res;
    return 0;
}
