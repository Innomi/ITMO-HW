#include <fstream>
#include <vector>

#define MOD 1000000007

using namespace std;

ifstream cin("problem4.in");
ofstream cout("problem4.out");

unsigned int n, m, k, l, b, e;
unsigned long long int matrix[100][100], res[100][100];

void multiply(unsigned long long int a[100][100], unsigned long long int b[100][100])
{
    unsigned long long int temp[100][100] = { 0 };
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            for (size_t k = 0; k < n; ++k)
            {
                temp[i][j] = (temp[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
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
    for (size_t i = 0; i < n; ++i)
    {
        res[i][i] = 1;
    }
    unsigned int accept[100];
    for (size_t i = 0; i < k; ++i)
    {
        cin >> accept[i];
        --accept[i];
    }
    char c;
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b >> e >> c;
        matrix[b - 1][e - 1] += 1;
    }
    matrixPow(l);
    unsigned long long int ans = 0;
    for (size_t i = 0; i < k; ++i)
    {
        ans = (ans + res[0][accept[i]]) % MOD;
    }
    cout << ans << endl;
    return 0;
}
