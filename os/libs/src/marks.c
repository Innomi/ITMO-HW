#include <stdio.h>

static void _wspace()
{
    putchar(' ');
}

static void _coma()
{
    putchar(',');
}

static void _excl()
{
    putchar('!');
}

static void _newl()
{
    putchar('\n');
}

typedef struct
{
    void (*wspace)();
    void (*coma)();
    void (*excl)();
    void (*newl)();
} marks;

marks getMarks()
{
    marks m = { _wspace, _coma, _excl, _newl };
    return m;
}
