#include <fstream>

using namespace std;

ifstream cin("bookshelf.in");
ofstream cout("bookshelf.out");

int n, l, h[2000], w[2000], d[2000][3];

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    cin >> n >> l;
    for (int i = 0; i < n; ++i)
    {
        cin >> h[i] >> w[i];
    }
    d[0][0] = h[0];
    d[0][1] = l - w[0];
    d[0][2] = h[0];
    int k = 1;
    while ((k < n) && (d[k - 1][1] - w[k] >= 0))
    {
        d[k][0] = max(h[k], d[k - 1][0]);
        d[k][1] = d[k - 1][1] - w[k];
        d[k][2] = d[k][0];
        ++k;
    }
    for (int i = k; i < n; ++i)
    {
        d[i][0] = d[i - 1][0] + h[i];
        d[i][1] = l - w[i];
        d[i][2] = h[i];
        int temp = i - 1, balance = d[i][1], tempH = h[i];
        while (balance - w[temp] >= 0)
        {
            tempH = max(tempH, h[temp]);
            balance -= w[temp];
            if (d[i][0] > d[temp - 1][0] + tempH)
            {
                d[i][2] = tempH;
                d[i][0] = d[temp - 1][0] + d[i][2];
                d[i][1] = balance;
            }
            --temp;
        }
        if ((d[i - 1][1] >= w[i]) && (d[i][0] > d[i - 1][0] - d[i - 1][2] + max(d[i - 1][2], h[i])))
        {
            d[i][2] = max(d[i - 1][2], h[i]);
            d[i][0] = d[i - 1][0] - d[i - 1][2] + d[i][2];
            d[i][1] = d[i - 1][1] - w[i];
        }
    }
    cout << d[n - 1][0];
    return 0;
}
