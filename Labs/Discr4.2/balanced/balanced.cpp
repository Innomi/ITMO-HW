#include <iostream>

using namespace std;

int main()
{
    freopen("balanced.out", "w", stdout);
    cout << "start: s\naccept: ac\nreject: rj\nblank: #\ns # -> ac # ^\ns ) -> rj # ^\ns ( -> f # >\ns * -> s # >\nf # -> rj # ^\nf ) -> r * <\nf ( -> f ( >\nf * -> f * >\nr ) -> r ) <\nr ( -> r ( <\nr * -> r * <\nr # -> s # >\n" << flush;
    return 0;
}
