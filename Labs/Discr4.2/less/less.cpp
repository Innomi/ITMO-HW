#include <iostream>

using namespace std;

int main()
{
    freopen("less.out", "w", stdout);
    cout << "start: ss\naccept: ac\nreject: rj\nblank: $\nss 0 -> ssr 2 >\nss 1 -> ssr 3 >\nssr 0 -> ssr 0 >\nssr 1 -> ssr 1 >\nssr < -> ssr < >\nssr 4 -> ssrl 4 <\nssr 5 -> ssrl 5 <\nssr $ -> ssrl $ <\nssrl 0 -> ssl 4 <\nssrl 1 -> ssl 5 <\nssrl < -> rj < ^\nssl 0 -> ssl 0 <\nssl 1 -> ssl 1 <\nssl < -> ssl < <\nssl 2 -> sslr 2 >\nssl 3 -> sslr 3 >\nsslr 0 -> ssr 2 >\nsslr 1 -> ssr 3 >\nsslr < -> ssc < >\nssc 0 -> ac 0 ^\nssc 1 -> ac 1 ^\nssc 4 -> scr 4 <\nssc 5 -> scr 5 <\nscr 2 -> scr 2 <\nscr 3 -> scr 3 <\nscr < -> scr < <\nscr $ -> cl $ >\ncl 0 -> cl 0 >\ncl 1 -> cl 1 >\ncl 2 -> cl 0 >\ncl 3 -> cl 1 >\ncl 4 -> cl 0 >\ncl 5 -> cl 1 >\ncl < -> cl < >\ncl $ -> r $ <\nr 0 -> r 0 <\nr 1 -> r 1 <\nr < -> r < <\nr $ -> s $ >\ns 0 -> rz 2 >\ns 1 -> rnz 3 >\ns < -> rj < ^\nrz 0 -> rz 0 >\nrz 1 -> rz 1 >\nrz < -> z < >\nz 2 -> z 2 >\nz 3 -> z 3 >\nz 0 -> l 2 <\nz 1 -> ac 1 ^\nz $ -> rj $ ^\nrnz 0 -> rnz 0 >\nrnz 1 -> rnz 1 >\nrnz < -> nz < >\nnz 2 -> nz 2 >\nnz 3 -> nz 3 >\nnz 0 -> rj 0 ^\nnz 1 -> l 3 <\nnz $ -> rj $ ^\nl 2 -> l 2 <\nl 3 -> l 3 <\nl < -> c < <\nc 0 -> c 0 <\nc 1 -> c 1 <\nc 2 -> s 2 >\nc 3 -> s 3 >\n" << flush;
    return 0;
}
