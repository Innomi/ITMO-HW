#include <iostream>
#include <vector>

using namespace std;

const long long INF = 1e12;

int main()
{
    freopen("assignment.in", "r", stdin);
    freopen("assignment.out", "w", stdout);
    
    unsigned int n;
    scanf("%u", &n);
    
    long long price;
    
    vector< vector<long long> > matrix;
    for (size_t row = 0; row < n; ++row)
    {
        matrix.push_back(vector<long long>());
        for (size_t col = 0; col < n; ++col)
        {
            scanf("%lld", &price);
            matrix[row].push_back(price);
        }
    }
    
    long long cost(0);
    
    vector<long long> rows(n);
    vector<long long> cols(n);
    vector<long long> marked(n, -1);
    
    for (size_t cur_row = 0; cur_row < n; ++cur_row)
    {
        long long marked_row = cur_row;
        long long marked_col = -1;
        long long cur_col;
        
        vector<long long> mins(n, INF);
        vector<bool> used(n, false);
        vector<long long> links(n, -1);
        
        while (marked_row != -1)
        {
            cur_col = -1;
            long long delta = INF;
            for (size_t col = 0; col < n; ++col)
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
            
            for (size_t col = 0; col < n; ++col)
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
    
    printf("%lld\n", cost);
    for (size_t i = 0; i < n; ++i)
    {
        if (marked[i] != -1)
        {
            printf("%lld %lu\n", marked[i] + 1, i + 1);
        }
    }
    
    return 0;
}
