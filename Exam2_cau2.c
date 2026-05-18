#include <stdio.h>

void heSo4(int x)
{
    if (x >= 4)
    {
        heSo4(x / 4);
    }
    putchar('0' + (x % 4));
}

int main(void)
{
    int x;
    if (scanf("%d", &x) == 1)
    {
        if (x == 0)
        {
            putchar('0');
        }
        else
        {
            heSo4(x);
        }
        putchar('\n');
    }
    return 0;
}
