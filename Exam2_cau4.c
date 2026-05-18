#include <stdio.h>

void inMang(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d", a[i]);
        if (i < n - 1)
            printf(" ");
    }
    printf("\n");
}

void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int daDoi = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] < a[j + 1])
            {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                daDoi = 1;
            }
        }

        inMang(a, n);
        if (!daDoi)
            break;
    }
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1)
        return 0;

    int a[100];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    bubbleSort(a, n);
    return 0;
}
