#include <iostream>
#include <string>
 
using namespace std;
 
int main()
{
    string b, s;
    //beg:
    getline(cin, b);
    getline(cin, s);
    short int **d = new short int*[b.length() + 1];
    for (int i = 0; i <= b.length(); ++i)
    {
        d[i] = new short int[s.length() + 1];
    }
    for (int i = 0; i <= b.length(); ++i)
    {
        for (int j = 0; j <= s.length(); ++j)
        {
            d[i][j] = 0;
        }
    }
    d[0][0] = 1;
     
    for (int i = 1; i <= b.length(); ++i)
    {
        for (int j = 0; j <= s.length(); ++j)
        {
            if (j > 0)
            {
                if ((b[i - 1] == '?') || (b[i - 1] == s[j - 1]))
                {
                    d[i][j] = d[i - 1][j - 1];
                }
            }
            if (b[i - 1] == '*')
            {
                if (j > 0)
                {
                    d[i][j] = d[i - 1][j - 1] | d[i - 1][j] | d[i][j - 1];
                }
                else
                {
                    d[i][j] = d[i - 1][j];
                }
            }
        }
    }
     
    if (d[b.length()][s.length()])
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
    /*
    cout << endl;
    for (int i = 0; i <= b.length(); ++i)
    {
        for (int j = 0; j <= s.length(); ++j)
        {
            cout << d[i][j] << ' ';
        }
        cout << endl;
    }
    */
    //goto beg;
    return 0;
}
