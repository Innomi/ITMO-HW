#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>

#define MOD 1000000007

using namespace std;

ifstream cin("problem5.in");
ofstream cout("problem5.out");

unsigned int n, m, k, l, b, e, new_n, nk;
unsigned long long int matrix[101][101], res[101][101];

struct state
{
    string states;
    state()
    {
        for (size_t i = 0; i < 101; ++i)
        {
            states += '0';
        }
    };
    state(state *a)
    {
        states = a->states;
    };
    bool operator<(const state & x) const
    {
        return this->states < x.states;
    }
};

void multiply(unsigned long long int a[101][101], unsigned long long int b[101][101])
{
    unsigned long long int temp[101][101] = { 0 };
    for (size_t i = 0; i < new_n; ++i)
    {
        for (size_t j = 0; j < new_n; ++j)
        {
            for (size_t k = 0; k < new_n; ++k)
            {
                temp[i][j] = (temp[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    for (size_t i = 0; i < new_n; ++i)
    {
        for (size_t j = 0; j < new_n; ++j)
        {
            a[i][j] = temp[i][j];
        }
    }
}

void matrixPow(unsigned int pow)
{
    while (pow)
    {
        if (pow & 1)
        {
            multiply(res, matrix);
            --pow;
        }
        else
        {
            multiply(matrix, matrix);
            pow >>= 1;
        }
    }
}

int main()
{
    cin >> n >> m >> k >> l;
    vector< vector< vector<unsigned int> > > edges(n, vector< vector<unsigned int> >(26, vector<unsigned int>()));
    unsigned int accept[101], new_accept[101] = { 0 };
    for (size_t i = 0; i < k; ++i)
    {
        cin >> accept[i];
        --accept[i];
        if (accept[i] == 0)
        {
            new_accept[nk++] = 0;
        }
    }
    char c;
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e >> c;
        edges[b - 1][c - 'a'].push_back(e - 1);
    }
    map<state, unsigned int> used;
    state s;
    s.states[0] = '1';
    used[s] = new_n++;
    queue<state> q;
    q.push(s);
    //bool add;
    while (!q.empty())
    {
        state st(q.front());
        q.pop();
        for (size_t i = 0; i < 26; ++i)
        {
            //add = false;
            state nst;
            for (size_t j = 0; j < n; ++j)
            {
                if (st.states[j] == '1')
                {
                    for (size_t k = 0; k < edges[j][i].size(); ++k)
                    {
                        nst.states[edges[j][i][k]] = '1';
                        //add = true;
                    }
                }
            }
            if (!used.count(nst)/* && add*/)
            {
                /*for (size_t i = 0; i < 100; ++i)
                {
                    cout << nst.states[i] << ' ';
                }
                cout << endl << endl << endl;*/
                q.push(nst);
                used[nst] = new_n;
                for (size_t j = 0; j < k; ++j)
                {
                    if (nst.states[accept[j]] == '1')
                    {
                        new_accept[nk++] = new_n;
                        break;
                    }
                }
                matrix[used[st]][new_n] += 1;
                ++new_n;
            }
            else
            {
                //if (add)
                //{
                    matrix[used[st]][used[nst]] += 1;
                //}
            }
        }
    }
    for (size_t i = 0; i < new_n; ++i)
    {
        res[i][i] = 1;
    }
    matrixPow(l);
    //cout << new_n << endl;
    unsigned long long int ans = 0;
    /*for (size_t i = 0; i < new_n; ++i)
    {
        for (size_t j = 0; j < new_n; ++j)
        {
            cout << res[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;*/
    for (size_t i = 0; i < nk; ++i)
    {
        //cout << new_accept[i] << ' ';
        ans = (ans + res[0][new_accept[i]]) % MOD;
    }
    //cout << endl;
    cout << ans;
    return 0;
}
