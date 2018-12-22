while (<>) {
    s/<.+?>//g;
    if (/[^ \n]/) {
        s/^ +//;
        s/ +$//;
        s/ +/ /g;
        print;
        last;
    }
}
while (<>) {
    s/<.+?>//g;
    if (/^ *$/) {
        while (<>) {
            s/<.+?>//g;
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
