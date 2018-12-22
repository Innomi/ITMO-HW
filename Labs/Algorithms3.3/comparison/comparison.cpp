#include <iostream>
#include <vector>
#include <string>

using namespace std;

const unsigned long long P = 37;

int main()
{
    char c = getchar();
    vector<unsigned long long> hash(1, 0);
    vector<unsigned long long> dividers;
    unsigned long long cur(1), last(0);
    while (c != '\n')
    {
        dividers.emplace_back(cur);
        last += (c - 'a' + 1) * cur;
        hash.emplace_back(last);
        cur *= P;
        c = getchar();
    }
    unsigned int m;
    unsigned long long hash1, hash2, b1, e1, b2, e2, deg;
    cin >> m;
    for (size_t i = 0; i < m; ++i)
    {
        cin >> b1 >> e1 >> b2 >> e2;
        if (b1 > b2)
        {
            swap(b1, b2);
            swap(e1, e2);
        }
        deg = b2 - b1;
        b1 = hash[b1 - 1] * dividers[deg];
        e1 = hash[e1] * dividers[deg];
        b2 = hash[b2 - 1];
        e2 = hash[e2];
        hash1 = e1 - b1;
        hash2 = e2 - b2;
        if (hash1 != hash2)
        {
            cout << "No" << endl;
        }
        else
        {
            cout << "Yes" << endl;
        }
    }
    return 0;
}
