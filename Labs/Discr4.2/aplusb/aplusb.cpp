#include <iostream>

using namespace std;

int main()
{
    freopen("aplusb.out", "w", stdout);
    cout << "start: s\naccept: ac\nreject: rj\nblank: =\ns 1 -> r 1 >\ns 0 -> r 0 >\nr 0 -> r 0 >\nr 1 -> r 1 >\nr 2 -> r 2 >\nr 3 -> r 3 >\nr + -> r + >\nr = -> b = <\nb 0 -> bz = <\nb 1 -> bnz = <\nb + -> end = <\nbz 1 -> bz 1 <\nbz 0 -> bz 0 <\nbz + -> az + <\naz 2 -> az 2 <\naz 3 -> az 3 <\naz 0 -> r 2 >\naz 1 -> r 3 >\naz = -> r 2 >\nbnz 1 -> bnz 1 <\nbnz 0 -> bnz 0 <\nbnz + -> anz + <\nanz 2 -> anz 2 <\nanz 3 -> anz 3 <\nanz 0 -> r 3 >\nanz 1 -> canz 2 <\nanz = -> r 3 >\ncanz 0 -> r 1 >\ncanz 1 -> canz 0 <\ncanz = -> r 1 >\nend 3 -> end 1 <\nend 2 -> end 0 <\nend 1 -> end 1 <\nend 0 -> end 0 <\nend = -> ac = >\n" << flush;
  return 0;
}

