#include <fstream>
 
using namespace std;
ifstream cin("pathsg.in");
ofstream cout("pathsg.out");
 
int main()
{
    int n, m, b, e, c, t[200][200];
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            t[i][j] = 1000000;
        }
        t[i][i] = 0;
    }
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> b >> e >> c;
            t[b - 1][e - 1] = c;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                if (t[j][k] > t[j][i] + t[i][k])
                {
                    t[j][k] = t[j][i] + t[i][k];
                }
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << t[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
