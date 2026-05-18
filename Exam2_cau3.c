#include <stdio.h>

float ab(float x)
{
    return x < 0 ? -x : x;
}

float canBacHai(int a)
{
    float x = a;
    if (x < 1.0f)
    {
        x = 1.0f;
    }

    while (1)
    {
        float xn = (x * x + a) / (2.0f * x);
        if (ab(xn - x) / xn < 0.0001f)
        {
            return xn;
        }
        x = xn;
    }
}

int main()
{
    int a;
    if (scanf("%d", &a) == 1)
    {
        float kq = canBacHai(a);
        printf("%.6g\n", kq);
    }
    return 0;
}
