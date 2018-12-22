while (<>) {
    if (/[^ \n]/) {
        s/^ +//;
        s/ +$//;
        s/ +/ /g;
        print;
        last;
    }
}
while (<>) {
    if (/^ *$/) {
        while (<>) {
            if (/[^ \n]/) {
                print "\n";
                s/^ +//;
                s/ +$//;
                s/ +/ /g;
                print;
                last;
            }
        }
    } else {
        s/^ +//;
        s/ +$//;
        s/ +/ /g;
        print;
    }
}
