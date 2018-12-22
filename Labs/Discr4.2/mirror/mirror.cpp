#include <iostream>

using namespace std;

int main()
{
    freopen("mirror.out", "w", stdout);
    cout << "start: s\naccept: ac\nreject: rj\nblank: ~\ns 0 -> r 2 >\ns 1 -> r 3 >\nr 0 -> r 2 >\nr 1 -> r 3 >\nr ~ -> c ~ <\nc 0 -> c 0 <\nc 1 -> c 1 <\nc 2 -> pz 0 >\nc 3 -> pnz 1 >\nc ~ -> ac ~ >\npz 0 -> pz 0 >\npz 1 -> pz 1 >\npz ~ -> c 0 <\npnz 0 -> pnz 0 >\npnz 1 -> pnz 1 >\npnz ~ -> c 1 <\n" << flush;
 return 0;
}
