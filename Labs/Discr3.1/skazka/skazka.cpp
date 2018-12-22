#include <bits/stdc++.h>

using namespace std;

unsigned int mas[1000], temp[1000];

void merge(size_t b, size_t e)
{
    size_t i = b, j = (b + e) / 2 + 1;
    while (i != (b + e) / 2 + 1 && j != e + 1)
    {
        cout << "1 " << mas[i] << " " << mas[j] << endl;
        string s;
        cin >> s;
        if (s == "YES")
        {
            temp[i + j - ((b + e) / 2 + 1)] = mas[i];
            ++i;
        }
        else
        {
            temp[i + j - ((b + e) / 2 + 1)] = mas[j];
            ++j;
        }
    }
    if (j == e + 1)
    {
        while (i != (b + e) / 2 + 1)
        {
            temp[i + j - ((b + e) / 2 + 1)] = mas[i];
            ++i;
        }
    }
    else
    {
        while (j != e + 1)
        {
            temp[i + j - ((b + e) / 2 + 1)] = mas[j];
            ++j;
        }
    }
    for (size_t k = b; k <= e; ++k)
    {
        mas[k] = temp[k];
    }
}

void mergeSort(size_t b, size_t e)
{
    if (e != b)
    {
        mergeSort(b, (b + e) / 2);
        mergeSort((b + e) / 2 + 1, e);
        merge(b, e);
    }
}

int main()
{
    size_t n;
    cin >> n;
    for (size_t i = 1; i <= n; ++i)
    {
        mas[i - 1] = i;
    }
    mergeSort(0, n - 1);
    cout << "0 ";
    for (size_t i = 0; i < n; ++i)
    {
        cout << mas[i] << " ";
    }
    cout << endl;
    return 0;
}
