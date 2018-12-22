#include <unordered_set>
#include <vector>
#include <queue>
#include <map>
#include <iterator>
#include <fstream>

using namespace std;

ifstream cin("fastminimization.in");
ofstream cout("fastminimization.out");

unsigned int n, m, k;
vector< vector<unsigned int> > newEdges;
vector< vector<unsigned int> > newBackEdges;
bool isReachable[50001];
bool isReachable1[50001];

void reach(unsigned int u)
{
    isReachable[u] = true;
    for (size_t i = 0; i < newBackEdges[u].size(); ++i)
    {
        if (!isReachable[newBackEdges[u][i]])
        {
            reach(newBackEdges[u][i]);
        }
    }
}

void reachF(unsigned int u)
{
    isReachable1[u] = true;
    for (size_t i = 0; i < 26; ++i)
    {
        if (!isReachable1[newEdges[u][i]] && newEdges[u][i] != n)
        {
            reachF(newEdges[u][i]);
        }
    }
}

int main()
{
    cin >> n >> m >> k;
    bool T[50001] = { 0 }; // T - terminal states
    for (size_t i = 0; i < k; ++i)
    {
        unsigned int v;
        cin >> v;
        T[v - 1] = true;
    }
    vector< unordered_set<unsigned int> > P; //P - partition
    queue< pair<unsigned int, unsigned int> > q; //Queue of pairs <num of class in P, char>
    vector< vector<unsigned int> > frontEdges(n + 1, vector<unsigned int>(26, n));
    vector< vector< vector<unsigned int> > > edges(n + 1, vector< vector<unsigned int> >(26, vector<unsigned int>())); //Array of arrays of states which you can reach with 1 step from state A using char C;
    for (size_t i = 0; i < m; ++i)
    {
        unsigned int b, e;
        char c;
        cin >> b >> e >> c;
        frontEdges[b - 1][c - 'a'] = e - 1;
        //edges[e - 1][c - 'a'].push_back(b - 1);
    }
    n++;
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < 26; ++j)
        {
            edges[frontEdges[i][j]][j].push_back(i);
        }
    }
    unsigned int indInP[50001];
    unordered_set<unsigned int> term;
    unordered_set<unsigned int> notTerm;
    for (size_t i = 0; i < n; ++i)
    {
        if (T[i])
        {
            indInP[i] = 0;
            term.insert(i);
        }
        else
        {
            indInP[i] = 1;
            notTerm.insert(i);
        }
    }
    P.push_back(term);
    P.push_back(notTerm);
    for (size_t i = 0; i < 26; ++i)
    {
        q.push(make_pair(0, i));
        q.push(make_pair(1, i));
    }
    map < unsigned int, vector<unsigned int> > inv;
    while (!q.empty())
    {
        pair<unsigned int, unsigned int> cur = q.front();
        q.pop();
        inv.clear();
        for (unordered_set<unsigned int>::iterator i = P[cur.first].begin(); i != P[cur.first].end(); ++i)
        {
            for (size_t j = 0; j < edges[*i][cur.second].size(); ++j)
            {
                unsigned int t = indInP[edges[*i][cur.second][j]];
                if (!inv.count(t))
                {
                    vector<unsigned int> temp;
                    inv[t] = temp;
                }
                inv[t].push_back(edges[*i][cur.second][j]);
            }
        }
        for (map< unsigned int, vector<unsigned int> >::iterator i = inv.begin(); i != inv.end(); ++i)
        {
            if (i->second.size() < P[i->first].size())
            {
                unordered_set<unsigned int> temp;
                if (P[P.size() - 1].size() == 0)
                {
                    P.pop_back();
                }
                unsigned int ind = P.size();
                P.push_back(temp);
                for (size_t j = 0; j < i->second.size(); ++j)
                {
                    P[i->first].erase(i->second[j]);
                    P[ind].insert(i->second[j]);
                }
                if (P[ind].size() > P[i->first].size())
                {
                    swap(P[ind], P[i->first]);
                }
                for (unordered_set<unsigned int>::iterator j = P[ind].begin(); j != P[ind].end(); ++j)
                {
                    indInP[*j] = ind;
                }
                if (P[ind].size() > 0)
                {
                    for (size_t j = 0; j < 26; ++j)
                    {
                        q.push(make_pair(ind, j));
                    }
                }
            }
        }
    }
    /*for (size_t i = 0; i < P.size(); ++i)
    {
        cout << P[i].size() << ' ';
    }
    cout << endl;*/
    for (size_t i = 0; i < n; ++i)
    {
        vector<unsigned int> temp(26, n);
        newEdges.push_back(temp);
    }
    vector<unsigned int> newT;
    vector<unsigned int> loli;
    unsigned int newN = 0, newM = 0;
    for (size_t i = 0; i < P.size(); ++i)
    {
        if (P[i].count(0))
        {
            swap(P[0], P[i]);
            for (unordered_set<unsigned int>::iterator j = P[0].begin(); j != P[0].end(); ++j)
            {
                indInP[*j] = 0;
            }
            for (unordered_set<unsigned int>::iterator j = P[i].begin(); j != P[i].end(); ++j)
            {
                indInP[*j] = i;
            }
            break;
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        vector<unsigned int> temp;
        newBackEdges.push_back(temp);
    }
    for (size_t i = 0; i < P.size(); ++i)
    {
        if (P[i].size() > 0)
        {
            ++newN;
        }
        if (!P[i].empty() && T[*P[i].begin()])
        {
            newT.push_back(i);
        }
        for (unordered_set<unsigned int>::iterator cur = P[i].begin(); cur != P[i].end(); ++cur)
        {
            for (size_t j = 0; j < 26; ++j)
            {
                if (newEdges[i][j] == n && frontEdges[*cur][j] != n - 1)
                {
                    ++newM;
                    newEdges[i][j] = indInP[frontEdges[*cur][j]];
                    newBackEdges[indInP[frontEdges[*cur][j]]].push_back(i);
                }
            }
        }
    }
    for (size_t i = 0; i < newT.size(); ++i)
    {
        reach(newT[i]);
    }
    reachF(0);
    for (size_t i = 0; i < newN; ++i)
    {
        //cout << isReachable[i] << ' ' << isReachable1[i] << endl;
        isReachable[i] = isReachable[i] && isReachable1[i];
    }
    //cout << *P[1].begin() << endl;
    unsigned int N = newN;
    //cout << newN << endl;
    for (size_t i = 0; i < N; ++i)
    {
        if (isReachable[i])
        {
            for (size_t j = 0; j < 26; ++j)
            {
                if (newEdges[i][j] != n && !isReachable[newEdges[i][j]])
                {
                    --newM;
                    newEdges[i][j] = n;
                }
            }
        }
        else
        {
            --newN;
            for (size_t j = 0; j < 26; ++j)
            {
                if (newEdges[i][j] != n)
                {
                    --newM;
                    newEdges[i][j] = n;
                }
            }
        }
    }
    unsigned int newInd[50001], newnewN = 0;
    bool used[50001] = { 0 };
    queue<unsigned int> q1;
    q1.push(0);
    used[0] = true;
    while (!q1.empty())
    {
        unsigned int cur = q1.front();
        q1.pop();
        newInd[cur] = newnewN;
        ++newnewN;
        for (size_t j = 0; j < 26; ++j)
        {
            if (newEdges[cur][j] != n && !used[newEdges[cur][j]])
            {
                q1.push(newEdges[cur][j]);
                used[newEdges[cur][j]] = true;
            }
        }
    }
    for (size_t i = 0; i < newT.size(); ++i)
    {
        if (isReachable[newT[i]])
        {
            loli.push_back(newT[i]);
        }
    }
    cout << newN << ' ' << newM << ' ' << loli.size() << '\n';
    for (size_t i = 0; i < loli.size(); ++i)
    {
        cout << newInd[loli[i]] + 1 << ' ';
    }
    cout << '\n';
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < 26; ++j)
        {
            if (newEdges[i][j] != n)
            {
                cout << newInd[i] + 1 << ' ' << newInd[newEdges[i][j]] + 1 << ' ' << (char)(j + 'a') << endl;
            }
        }
    }
    return 0;
}
