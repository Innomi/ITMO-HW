while (<>) {
    s/\(([^)]+)\)/\(\)/g;
    print;
}
