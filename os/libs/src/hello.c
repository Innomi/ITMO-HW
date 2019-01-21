#include <stdio.h>

static void _H()
{
    putchar('H');
}

static void _e()
{
    putchar('e');
}

static void _l()
{
    putchar('l');
}

static void _o()
{
    putchar('o');
}

typedef struct
{
    void (*H)();
    void (*e)();
    void (*l)();
    void (*o)();
} hello;

hello getHello()
{
    hello h = { _H, _e, _l, _o };
    return h;
}
