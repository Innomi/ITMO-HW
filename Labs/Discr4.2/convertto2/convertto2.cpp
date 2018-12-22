#include <iostream>

using namespace std;

int main()
{
    freopen("convertto2.out", "w", stdout);
    cout << "start: s\naccept: ac\nreject: rj\nblank: &\ns 0 -> s 0 <\ns 1 -> s 1 <\ns 2 -> s 2 <\ns & -> sz | <\nsz & -> r 0 >\nr 0 -> r 0 >\nr 1 -> r 1 >\nr 2 -> r 2 >\nr | -> r | >\nr & -> m & <\nm 2 -> l 1 <\nm 1 -> l 0 <\nm 0 -> m 2 <\nm | -> clr & >\nl 0 -> l 0 <\nl 1 -> l 1 <\nl 2 -> l 2 <\nl | -> p | <\np 0 -> r 1 >\np 1 -> p 0 <\np & -> r 1 >\nclr 2 -> clr & >\nclr & -> clr & <\nclr 0 -> end 0 <\nclr 1 -> end 1 <\nend 0 -> end 0 <\nend 1 -> end 1 <\nend & -> ac & >\n" << flush;
    return 0;
}
