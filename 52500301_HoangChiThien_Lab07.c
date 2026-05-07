#include <stdio.h>

int search(const int* arr, const int size, const int key)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr[i] == key) return i;
    }
    return -1;
}

int bsearch(const int* arr, const int size, const int key)
{
    int low = 0, high = size - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (key == arr[mid]) return mid;
        else if (key > arr[mid]) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void selectionSort(int *arr, int size)
{
    int i, j, maxIndex, temp;
    for (i = 0; i < size - 1; i++)
    {
        maxIndex = i;
        for (j = i + 1; j < size; j++)
        {
            if (arr[j] > arr[maxIndex])
                maxIndex = j;
        }
        temp = arr[i];
        arr[i] = arr[maxIndex];
        arr[maxIndex] = temp;
    }
}

void bubbleSort(int *arr, int size)
{
    int i, limit, temp;
    for (limit = size - 2; limit >= 0; limit--)
    {
        for (i = 0; i <= limit; i++)
        {
            if (arr[i] < arr[i+1])
            {
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
        }
    }
}

int main()
{
    int arr[]    = {5, 3, 8, 1, 9};
    int sorted[] = {1, 3, 5, 8, 9};
    int size = 5;
    int i;

    printf("1. %d\n", search(arr, size, 8));
    printf("2. %d\n", bsearch(sorted, size, 8));

    selectionSort(arr, size);
    printf("3. ");
    for (i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    int arr2[] = {5, 3, 8, 1, 9};
    bubbleSort(arr2, size);
    printf("4. ");
    for (i = 0; i < size; i++) printf("%d ", arr2[i]);
    printf("\n");

    return 0;
}