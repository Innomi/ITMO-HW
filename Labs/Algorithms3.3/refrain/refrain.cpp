#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

int main()
{
    freopen("refrain.in", "r", stdin);
    freopen("refrain.out", "w", stdout);
    unsigned int n, m;
    cin >> n >> m;
    unsigned int alphabet(m + 1), length(n + 1);
    vector<unsigned int> s(n + 1);
    for (size_t i = 0; i < n; ++i)
    {
        scanf("%u", &s[i]);
    }
    s[n] = 0;
    
    
    unsigned int classes(1);
    vector<int> sufArray(length);
    vector<int> temp(length); //It's for sort. Don't know how to name it. =(
    vector<unsigned int> c(length);
    vector<unsigned int> cnt(length);


    cnt.assign(alphabet, 0);
    for (size_t i = 0; i < length; ++i)
    {
        ++cnt[s[i]];
    }
    for (size_t i = 1; i < alphabet; ++i)
    {
        cnt[i] += cnt[i - 1];
    }
    for (size_t i = 0; i < length; ++i)
    {
        sufArray[--cnt[s[i]]] = i;
    }
    c[sufArray[0]] = 0;
    for (size_t i = 1; i < length; ++i)
    {
        if (s[sufArray[i]] != s[sufArray[i - 1]])
        {
            ++classes;
        }
        c[sufArray[i]] = classes - 1;
    }
    

    for (size_t k = 0; (unsigned int)(1 << k) < length; ++k)
    {
        for (size_t i = 0; i < length; ++i)
        {
            temp[i] = (sufArray[i] - (1 << k));
            if (temp[i] < 0)
            {
                temp[i] += length;
            }
        }
        
        
        cnt.assign(classes, 0);
        for (size_t i = 0; i < length; ++i)
        {
            ++cnt[c[temp[i]]];
        }
        for (size_t i = 1; i < classes; ++i)
        {
            cnt[i] += cnt[i - 1];
        }
        for (size_t i = length; i > 0; --i)
        {
            sufArray[--cnt[c[temp[i - 1]]]] = temp[i - 1];
        }
        
        
        vector<unsigned int> cn(length);
        cn[sufArray[0]] = 0;
        classes = 1;
        for (size_t i = 1; i < length; ++i)
        {
            if (c[sufArray[i]] == c[sufArray[i - 1]] && c[(sufArray[i] + (1 << k)) % length] == c[(sufArray[i - 1] + (1 << k)) % length])
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
    vector<unsigned int> lcpArray(sufArray.size() + 1);
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
    lcpArray[lcpArray.size() - 1] = 0;
    
    
    stack< pair<unsigned long long, unsigned long long> > st;
    //st.push(make_pair(0, 1));
    unsigned long long curL(0), curA(1), max(0), ind(0), l(0);
    for (size_t i = 1; i < length + 1; ++i)
    {
        if (curL == lcpArray[i])
        {
            ++curA;
            continue;
        }
        if (curL < lcpArray[i])
        {
            st.push(make_pair(curL, curA));
            curL = lcpArray[i];
            curA = 1;
            continue;
        }
        while (curL > lcpArray[i])
        {
            if (max < (curA + 1) * curL)
            {
                max = (curA + 1) * curL;
                ind = sufArray[i - curA];
                l = curL;
            }
            if (lcpArray[i] > st.top().first)
            {
                curL = lcpArray[i];
                break;
            }
            curL = st.top().first;
            curA += st.top().second;
            st.pop();
        }
        ++curA;
    }
    
    
    if(max >= length - 1)
    {
        printf("%llu\n%llu\n", max, l);
        for (size_t i = 0; i < l; ++i)
        {
            printf("%d ", s[ind + i]);
        }
    }
    else
    {
        printf("%d\n%d\n", length - 1, length - 1);
        for (size_t i = 0; i < length - 1; ++i)
        {
            printf("%d ", s[i]);
        }
    }
    /*printf("\n");
    for (size_t i = 0; i < sufArray.size(); ++i)
    {
        printf("%d ", sufArray[i]);
    }
    printf("\n");
    for (size_t i = 0; i < lcpArray.size() - 1; ++i)
    {
        printf("%d ", lcpArray[i]);
    }*/
    
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
