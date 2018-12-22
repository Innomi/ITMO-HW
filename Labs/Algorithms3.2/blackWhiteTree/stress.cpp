#include <iostream>

using namespace std;

const unsigned int N = 200000;

int main()
{
    freopen("test.in", "w", stdout);
    cout << N << ' ' << 2 << endl;
    for (size_t i = 1; i < N; ++i)
    {
        cout << i << ' ' << i + 1 << endl;
    }
    cout << "2 " << N / 2 << "\n2 " << N / 2 + 1 << endl;
    return 0;
}
