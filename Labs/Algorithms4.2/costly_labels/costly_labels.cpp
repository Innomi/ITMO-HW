#include <iostream>
#include <vector>

using namespace std;

const long long INF(1e9);

unsigned  int N, K, P;
vector< vector<unsigned int> > C;
vector< vector<unsigned int> > edges;
vector< vector< vector<int> > > dp;

long long hungarian(const vector< vector<long long> > & matrix)
{
    if (!matrix.size())
    {
        return 0;
    }
    unsigned long long n = matrix.size();
    unsigned long long m = matrix[0].size();
    long long cost(0);

    vector<long long> rows(n);
    vector<long long> cols(m);
    vector<long long> marked(m, -1);

    for (size_t cur_row = 0; cur_row < n; ++cur_row)
    {
        long long marked_row = cur_row;
        long long marked_col = -1;
        long long cur_col;
        
        vector<long long> mins(m, INF);
        vector<bool> used(m, false);
        vector<long long> links(m, -1);
        
        while (marked_row != -1)
        {
            cur_col = -1;
            long long delta = INF;
            for (size_t col = 0; col < m; ++col)
            {
                if (!used[col])
                {
                    long long cur = matrix[marked_row][col] - rows[marked_row] - cols[col];
                    if  (cur < mins[col])
                    {
                        mins[col] = cur;
                        links[col] = marked_col;
                    }
                    if (mins[col] < delta)
                    {
                        delta = mins[col];
                        cur_col = col;
                    }
                }
            }
            
            for (size_t col = 0; col < m; ++col)
            {
                if (used[col])
                {
                    rows[marked[col]] += delta;
                    cols[col] -= delta;
                }
                else
                {
                    mins[col] -= delta;
                }
            }
            
            cost += delta;
            
            rows[cur_row] += delta;
            used[cur_col] = true;
            marked_col = cur_col;
            marked_row = marked[marked_col];
        }
        
        while (true)
        {
            if (links[cur_col] == -1)
            {
                break;
            }
            marked[cur_col] = marked[links[cur_col]];
            cur_col = links[cur_col];
        }
        marked[cur_col] = cur_row;
    }

    return cost;
}

unsigned int dp_calc(unsigned int v, unsigned int col, unsigned int par, unsigned int par_col)
{
    if (dp[v][col][par_col] != -1)
    {
        return dp[v][col][par_col];
    }

    vector< vector<long long> > costs;
    for (size_t i = 0; i < edges[v].size(); ++i)
    {
        if (edges[v][i] != par)
        {
            vector<long long> tmp(K);
            for (size_t j = 0; j < K; ++j)
            {
                tmp[j] = dp_calc(edges[v][i], j, v, col) + C[edges[v][i]][j];
            }
            costs.emplace_back(move(tmp));
        }
    }

    unsigned int res(P), min_cost;
    for (size_t i = 0; i < costs.size(); ++i)
    {
        min_cost = INF;
        for (size_t j = 0; j < K; ++j)
        {
            min_cost = min(min_cost, (unsigned int)costs[i][j]);
        }
        res += min_cost;
    }
    if (costs.size() + (par != N ? 1 : 0) <= K)
    {
        if (par_col != K)
        {
            for (size_t i = 0; i < costs.size(); ++i)
            {
                costs[i][par_col] = INF;
            }
        }
        res = min(res, (unsigned int)hungarian(costs));
    }

    dp[v][col][par_col] = res;
    return res;
}

int main()
{
    scanf("%u %u %u", &N, &K, &P);

    C.assign(N, vector<unsigned int>(K));
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < K; ++j)
        {
            scanf("%u", &C[i][j]);
        }
    }
    
    edges.assign(N, vector<unsigned int>());
    unsigned int A, B;
    for (size_t i = 0; i < N - 1; ++i)
    {
        scanf("%u %u", &A, &B);
        edges[A - 1].emplace_back(B - 1);
        edges[B - 1].emplace_back(A - 1);
    }

    dp.assign(N, vector< vector<int> >(K + 1, vector<int>(K + 1, -1)));
    unsigned int ans = INF;
    for (size_t i = 0; i < K; ++i)
    {
        ans = min(ans, dp_calc(0, i, N, K) + C[0][i]);
    }
    printf("%u\n", ans);
}
