#include <iostream>

using namespace std;

int main()
{
    freopen("tandem.out", "w", stdout);
    cout << "start: s\naccept: ac\nreject: rj\nblank: @\ns 0 -> r 2 >\ns 1 -> r 3 >\nr 0 -> r 0 >\nr 1 -> r 1 >\nr 4 -> rl 4 <\nr 5 -> rl 5 <\nr @ -> rl @ <\nrl 0 -> l 4 <\nrl 1 -> l 5 <\nrl 2 -> rj 2 ^\nrl 3 -> rj 3 ^\nl 0 -> l 0 <\nl 1 -> l 1 <\nl 2 -> lr 2 >\nl 3 -> lr 3 >\nlr 0 -> r 2 >\nlr 1 -> r 3 >\nlr 4 -> cz 6 <\nlr 5 -> cnz 7 <\ncz 2 -> cz 2 <\ncz 3 -> cz 3 <\ncz 6 -> cz 6 <\ncz 7 -> cz 7 <\ncz 0 -> z 0 >\ncz 1 -> z 1 >\ncz @ -> z @ >\nz 2 -> c 0 >\nz 3 -> endr 3 ^\nc 2 -> c 2 >\nc 3 -> c 3 >\nc 6 -> c 6 >\nc 7 -> c 7 >\nc 4 -> cz 6 <\nc 5 -> cnz 7 <\nc @ -> enda @ ^\ncnz 2 -> cnz 2 <\ncnz 3 -> cnz 3 <\ncnz 6 -> cnz 6 <\ncnz 7 -> cnz 7 <\ncnz 0 -> nz 0 >\ncnz 1 -> nz 1 >\ncnz @ -> nz @ >\nnz 2 -> endr 2 ^\nnz 3 -> c 1 >\nendr 0 -> endr 0 <\nendr 1 -> endr 1 <\nendr 2 -> endr 2 <\nendr 3 -> endr 3 <\nendr 4 -> endr 4 <\nendr 5 -> endr 5 <\nendr 6 -> endr 6 <\nendr 7 -> endr 7 <\nendr @ -> endrj @ >\nenda 0 -> enda 0 <\nenda 1 -> enda 1 <\nenda 2 -> enda 2 <\nenda 3 -> enda 3 <\nenda 4 -> enda 4 <\nenda 5 -> enda 5 <\nenda 6 -> enda 6 <\nenda 7 -> enda 7 <\nenda @ -> endac @ >\nendrj 0 -> endrj @ >\nendrj 1 -> endrj @ >\nendrj 2 -> endrj @ >\nendrj 3 -> endrj @ >\nendrj 4 -> endrj @ >\nendrj 5 -> endrj @ >\nendrj 6 -> endrj @ >\nendrj 7 -> endrj @ >\nendrj @ -> rj @ ^\nendac 0 -> endac @ >\nendac 1 -> endac @ >\nendac 2 -> endac @ >\nendac 3 -> endac @ >\nendac 4 -> endac @ >\nendac 5 -> endac @ >\nendac 6 -> endac @ >\nendac 7 -> endac @ >\nendac @ -> ac @ ^\n" << flush;
    return 0;
}
