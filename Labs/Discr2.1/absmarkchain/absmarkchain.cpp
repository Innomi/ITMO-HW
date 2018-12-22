#include <fstream>

using namespace std;

ifstream cin("absmarkchain.in");
ofstream cout("absmarkchain.out");

int main()
{
    unsigned int n, m, a = 0, inq[2][160000];
    cin >> n >> m;
    float in[160000];
    bool abs[400];
    for (size_t i = 0; i < m; ++i)
    {
        cin >> inq[0][i] >> inq[1][i] >> in[i];
        inq[0][i] -= 1;
        inq[1][i] -= 1;
        if (inq[0][i] == inq[1][i] && in[i] == 1)
        {
            abs[inq[0][i]] = true;
            a++;
        }
    }
    unsigned int q = 0, r = 0, pos[400];
    for (size_t i = 0; i < n; ++i)
    {
        if (abs[i])
        {
            pos[i] = r;
            r++;
        }
        else
        {
            pos[i] = q;
            q++;
        }
    }
    float R[400][400], Q[400][400];
    for (size_t i = 0; i < m; ++i)
    {
        if (abs[inq[1][i]])
        {
            if (!abs[inq[0][i]])
            {
                R[pos[inq[0][i]]][pos[inq[1][i]]] = in[i];
            }
        }
        else
        {
            Q[pos[inq[0][i]]][pos[inq[1][i]]] = in[i];
        }
    }
    unsigned int na = n - a;
    float N[400][400], E[400][400];
    for (size_t i = 0; i < na; ++i)
    {
        N[i][i] = 1;
        E[i][i] = 1;
        for (size_t j = 0; j < na; ++j)
        {
            E[i][j] -= Q[i][j];
        }
    }
    for (size_t i = 0; i < na; ++i)
    {
        if (E[i][i] != 1)
        {
            float temp = E[i][i];
            for (size_t j = 0; j < na; ++j)
            {
                E[i][j] /= temp;
                N[i][j] /= temp;
            }
        }
        for (size_t k = 0; k < na; ++k)
        {
            if (i != k)
            {
                float temp = E[k][i];
                for (size_t j = 0; j < na; ++j)
                {
                    E[k][j] -= temp * E[i][j];
                    N[k][j] -= temp * N[i][j];
                }
            }
        }
    }
    float G[400][400] = { 0 };
    for (size_t i = 0; i < na; ++i)
    {
        for (size_t j = 0; j < a; ++j)
        {
            for (size_t k = 0; k < na; ++k)
            {
                G[i][j] += N[i][k] * R[k][j];
            }
        }
    }
    cout.precision(5);
    for (size_t i = 0; i < n; ++i)
    {
        float chance = 0;
        if (abs[i])
        {
            for (size_t j = 0; j < na; ++j)
            {
                chance += G[j][pos[i]];
            }
            chance += 1;
            chance /= n;
        }
        cout << chance << "\n";
    }
    cout.flush();
    return 0;
}
