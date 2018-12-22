#include <iostream>

using namespace std;

int main()
{
    char c;
    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
            case '"':
                putchar('\\');
                putchar('"');
                break;
            case '\\':
                putchar('\\');
                putchar('\\');
                break;
            case '\n':
                putchar('\\');
                putchar('n');
                break;
            default:
                putchar(c);
        }
    }
    return 0;
}
