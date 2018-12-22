#include <iostream>

using namespace std;

int main()
{
    freopen("zero.out", "w", stdout);
    cout <<
        "start: s\n" <<
        "accept: ac\n" <<
        "reject: rj\n" <<
        "blank: -\n" <<
        "s - -> ac - ^\n" <<
        "s 0 -> n - >\n" <<
        "n 0 -> s - >\n" <<
        "n - -> rj - >\n"
    << flush;
    return 0;
}
