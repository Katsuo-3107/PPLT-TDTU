#include <stdio.h>

void xuatMang(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d", a[i]);
        if (i < n - 1)
        {
            printf(" ");
        }
    }
}

void doiCho(int a[], int i, int j)
{
    int tam;
    tam = a[i];
    a[i] = a[j];
    a[j] = tam;
}

void bubbleSort(int a[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                doiCho(a, j, j + 1);
            }
        }
        xuatMang(a, n);
        printf("\n");
    }
}

int main()
{
    int a[100];
    int n;
    scanf("%d", &n);
    int i;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    bubbleSort(a, n);

    return 0;
}