#include <iostream>

using namespace std;

int main()
{
    freopen("reverse.out", "w", stdout);
    cout << "start: s\naccept: ac\nreject: rj\nblank: !\ns 0 -> r 2 >\ns 1 -> r 3 >\nr 0 -> r 2 >\nr 1 -> r 3 >\nr ! -> c ! <\nc 0 -> c 0 <\nc 1 -> c 1 <\nc 4 -> c 4 <\nc 5 -> c 5 <\nc 2 -> pz 4 >\nc 3 -> pnz 5 >\nc ! -> end ! >\npz 0 -> pz 0 >\npz 1 -> pz 1 >\npz 4 -> pz 4 >\npz 5 -> pz 5 >\npz ! -> c 0 <\npnz 0 -> pnz 0 >\npnz 1 -> pnz 1 >\npnz 4 -> pnz 4 >\npnz 5 -> pnz 5 >\npnz ! -> c 1 <\nend 4 -> end ! >\nend 5 -> end ! >\nend 0 -> ac 0 ^\nend 1 -> ac 1 ^\n" << flush;
    return 0;
}
