#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const unsigned int ALPHABET = 256;
const unsigned int MAXLEN = 400001;

int main()
{
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    char ch;
    string s;
    while ((ch = getchar()) >= 'a' && ch <= 'z')
    {
        s += ch;
    }
    s += '$';
    
    
    size_t n = s.length();
    unsigned int classes(1);
    vector<int> sufArray(n);
    vector<int> temp(n); //It's for sort. Don't know how to name it. =(
    vector<unsigned int> c(MAXLEN);
    vector<unsigned int> cnt(MAXLEN);


    cnt.assign(ALPHABET, 0);
    for (size_t i = 0; i < n; ++i)
    {
        ++cnt[s[i]];
    }
    for (size_t i = 1; i < ALPHABET; ++i)
    {
        cnt[i] += cnt[i - 1];
    }
    for (size_t i = 0; i < n; ++i)
    {
        sufArray[--cnt[s[i]]] = i;
    }
    c[sufArray[0]] = 0;
    for (size_t i = 1; i < n; ++i)
    {
        if (s[sufArray[i]] != s[sufArray[i - 1]])
        {
            ++classes;
        }
        c[sufArray[i]] = classes - 1;
    }
    

    for (size_t k = 0; (unsigned int)(1 << k) < n; ++k)
    {
        for (size_t i = 0; i < n; ++i)
        {
            temp[i] = (sufArray[i] - (1 << k));
            if (temp[i] < 0)
            {
                temp[i] += n;
            }
        }
        
        
        cnt.assign(classes, 0);
        for (size_t i = 0; i < n; ++i)
        {
            ++cnt[c[temp[i]]];
        }
        for (size_t i = 1; i < classes; ++i)
        {
            cnt[i] += cnt[i - 1];
        }
        for (size_t i = n; i > 0; --i)
        {
            sufArray[--cnt[c[temp[i - 1]]]] = temp[i - 1];
        }
        
        
        vector<unsigned int> cn(MAXLEN);
        cn[sufArray[0]] = 0;
        classes = 1;
        for (size_t i = 1; i < n; ++i)
        {
            if (c[sufArray[i]] == c[sufArray[i - 1]] && c[(sufArray[i] + (1 << k)) % n] == c[(sufArray[i - 1] + (1 << k)) % n])
            {
                cn[sufArray[i]] = cn[sufArray[i - 1]];
            }
            else
            {
                cn[sufArray[i]] = cn[sufArray[i - 1]] + 1;
                ++classes;
            }
        }
        c = move(cn);
    }
    
    
    vector<unsigned int> rSufArray(sufArray.size());
    vector<unsigned int> lcpArray(sufArray.size());
    for (size_t i = 0; i < sufArray.size(); ++i)
    {
        rSufArray[sufArray[i]] = i;
    }
    int x = 0;
    for (size_t i = 0; i < rSufArray.size(); ++i)
    {
        x = max(x - 1, 0);
        if (rSufArray[i] == sufArray.size() - 1)
        {
            lcpArray[sufArray.size() - 1] = 0;
            x = 0;
        }
        else
        {
            unsigned int j = sufArray[rSufArray[i] + 1];
            while (max((unsigned int)i + x, j + x) < sufArray.size() && s[i + x] == s[j + x])
            {
                ++x;
            }
            lcpArray[rSufArray[i]] = x;
        }
    }
    
    
    unsigned long long ans = 0;
    
    
    for (size_t i = 0; i < sufArray.size(); ++i)
    {
        ans += n - sufArray[i] - 1 - lcpArray[i];
    }
    
    
    printf("%lld", ans);
    
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
