#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    void (*H)();
    void (*e)();
    void (*l)();
    void (*o)();
} hello;

typedef struct
{
    void (*w)();
    void (*o)();
    void (*r)();
    void (*l)();
    void (*d)();
} world;

typedef struct
{
    void (*wspace)();
    void (*coma)();
    void (*excl)();
    void (*newl)();
} marks;

hello getHello();
world getWorld();

int main()
{
    char* error;
    void* handle = dlopen("libmarks.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror();

    marks (*getMarks)() = dlsym(handle, "getMarks");

    error = dlerror();
    if (error != NULL)
    {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    
    hello h = getHello();
    world w = getWorld();
    marks m = getMarks();
    h.H();
    h.e();
    h.l();
    h.l();
    h.o();
    m.coma();
    m.wspace();
    w.w();
    w.o();
    w.r();
    w.l();
    w.d();
    m.excl();
    m.newl();

    dlclose(handle);
    exit(EXIT_SUCCESS);
}
