#include <stdio.h>

static void _w()
{
    putchar('w');
}

static void _o()
{
    putchar('o');
}

static void _r()
{
    putchar('r');
}

static void _l()
{
    putchar('l');
}

static void _d()
{
    putchar('d');
}

typedef struct
{
    void (*w)();
    void (*o)();
    void (*r)();
    void (*l)();
    void (*d)();
} world;

world getWorld()
{
    world w = { _w, _o, _r, _l, _d };
    return w;
}
