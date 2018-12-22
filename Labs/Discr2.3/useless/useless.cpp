#include <bits/stdc++.h>

using namespace std;

unsigned int cntr[100];
bool isGen[26];
vector< vector<unsigned int> > inRls;
string notT;

inline __attribute__((always_inline)) string getString(unsigned int rl)
{
    register char c = getchar();
    while (c == ' ')
    {
        c = getchar();
    }
    string ans;
    if (c == '\n')
    {
        return ans;
    }
    while (c != '\n' && c != ' ')
    {
        if (c >= 'A' && c <= 'Z')
        {
            bool contained = false;
            for (size_t i = 0; i < inRls[c - 'A'].size(); ++i)
            {
                if (inRls[c - 'A'][i] == rl)
                {
                    contained = true;
                }
            }
            if (!contained)
            {
                inRls[c - 'A'].push_back(rl);
                cntr[rl]++;
                if (notT.find(c) == string::npos)
                {
                    notT += c;
                }
            }
        }
        ans += c;
        c = getchar();
    }
    return ans;
}

int main()
{
    freopen("useless.in", "r", stdin);
    freopen("useless.out", "w", stdout);
    string s;
    unsigned int n, start;
    char c;
    vector< pair<char, string> > rules;
    cin >> n >> c;
    notT += c;
    for (size_t i = 0; i < 26; ++i)
    {
        vector<unsigned int> temp;
        inRls.push_back(temp);
    }
    start = c - 'A';
    queue<char> q;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> c >> s;
        if (notT.find(c) == string::npos)
        {
            notT += c;
        }
        s = getString(i);
        if (!cntr[i] && !isGen[c - 'A'])
        {
            isGen[c - 'A'] = true;
            q.push(c);
        }
        rules.push_back(make_pair(c, s));
    }
    while (!q.empty())
    {
        char cur = q.front();
        q.pop();
        for (size_t i = 0; i < inRls[cur - 'A'].size(); ++i)
        {
            if (cntr[inRls[cur - 'A'][i]] > 0)
            {
                cntr[inRls[cur - 'A'][i]]--;
            }
            if (!cntr[inRls[cur - 'A'][i]] && !isGen[rules[inRls[cur - 'A'][i]].first - 'A'])
            {
                isGen[rules[inRls[cur - 'A'][i]].first - 'A'] = true;
                q.push(rules[inRls[cur - 'A'][i]].first);
            }
        }
    }
    bool isRchbl[26] = { 0 };
    vector< vector<unsigned int> > edges(26, vector<unsigned int>());
    for (size_t i = 0; i < rules.size(); ++i)
    {
        if (!cntr[i])
        {
            for (size_t j = 0; j < rules[i].second.size(); ++j)
            {
                if (rules[i].second[j] >= 'A' && rules[i].second[j] <= 'Z')
                {
                    edges[rules[i].first - 'A'].push_back(rules[i].second[j] - 'A');
                }
            }
        }
    }
    queue<unsigned int> q1;
    if (isGen[start])
    {
        q1.push(start);
        isRchbl[start] = true;
    }
    while (!q1.empty())
    {
        unsigned int cur = q1.front();
        q1.pop();
        for (size_t i = 0; i < edges[cur].size(); ++i)
        {
            if (!isRchbl[edges[cur][i]])
            {
                isRchbl[edges[cur][i]] = true;
                q1.push(edges[cur][i]);
            }
        }
    }
    sort(notT.begin(), notT.end());
    for (size_t i = 0; i < notT.size(); ++i)
    {
        if (!isGen[notT[i] - 'A'] || !isRchbl[notT[i] - 'A'])
        {
            cout << notT[i] << ' ';
        }
    }
    return 0;
}
