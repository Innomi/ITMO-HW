#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<bool> isIndependent;

void setDependent(unsigned int num)
{
    isIndependent[num] = false;
    if (num == isIndependent.size() - 1)
    {
        return;
    }
    for (size_t i = 1; i < isIndependent.size(); i = i << 1)
    {
        if (!(i & num) && isIndependent[i | num])
        {
            setDependent(i | num);
        }
    }
}

int main()
{
    freopen("cycles.in", "r", stdin);
    freopen("cycles.out", "w", stdout);
    unsigned int n, m, size, elem, cycle, w, maxSize(0), maxW(0);
    cin >> n >> m;
    vector<unsigned int> wEls(n);
    isIndependent.resize(1 << n, true);
    for (size_t i = 0; i < n; ++i)
    {
        cin >> wEls[i];
    }
    for (size_t i = 0; i < m; ++i)
    {
        cycle = 0;
        cin >> size;
        for (size_t j = 0; j < size; ++j)
        {
            cin >> elem;
            cycle += 1 << (elem - 1);
        }
        setDependent(cycle);
    }
    for (size_t i = 0; i < isIndependent.size(); ++i)
    {
        if (isIndependent[i])
        {
            size = 0;
            w = 0;
            for (size_t j = 0; j < n; ++j)
            {
                if (i & (1 << j))
                {
                    w += wEls[j];
                    ++size;
                }
            }
            if (size > maxSize)
            {
                maxSize = size;
                maxW = w;
            }
            if (size == maxSize && maxW < w)
            {
                maxW = w;
            }
        }
    }
    cout << maxW;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
