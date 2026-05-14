#include <stdio.h>
#include <string.h>

#define MAX 1000

void write(char *filename, int sum) {
    FILE *fo = fopen(filename, "w");
    fprintf(fo, "%d", sum);
    fclose(fo);
}

int sumNumbers(char *filename, int n) {
    int sum = 0;
    int num;
    FILE *fi = fopen(filename, "r");
    for (int i = 0; i < n; i++) {
        fscanf(fi, "%d", &num);
        sum += num;
    }
    fclose(fi);
    return sum;
}

void stringLength(char *filename) {
    FILE *fi = fopen(filename, "r");
    char str[256];
    fgets(str, sizeof(str), fi);
    FILE *fo = fopen("output02.txt", "w");
    char *token = strtok(str, " \n");
    while (token != NULL) {
        int len = strlen(token);
        fprintf(fo, "%d ", len);
        token = strtok(NULL, " \n");
    }
    fclose(fi);
    fclose(fo);
}

void oldCode() {
    int sum = sumNumbers("input01.txt", 20);
    write("output01.txt", sum);
    stringLength("input02.txt");
}

int readNumbers(char *filename, int a[]) {
    FILE *fi = fopen(filename, "r");
    int n = 0;
    int number;

    if (fi == NULL) {
        printf("Cannot open file\n");
        return 0;
    }

    while (fscanf(fi, "%d", &number) == 1) {
        a[n] = number;
        n++;
    }

    fclose(fi);
    return n;
}

int linearSearch(int a[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (a[i] == key) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int a[], int n, int key) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (a[mid] == key) {
            return mid;
        } else if (a[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    char filename[100];
    int a[MAX];
    int n;
    int key;
    int position = -1;
    int choose;

    printf("enter a filename:");
    scanf("%s", filename);

    n = readNumbers(filename, a);

    printf("1. linear search\n");
    printf("2. binary search\n");

    printf("choose one of these search algorithms:");
    scanf("%d", &choose);

    printf("enter a value to search for:");
    scanf("%d", &key);

    if (choose == 1) {
        position = linearSearch(a, n, key);
    } else if (choose == 2) {
        position = binarySearch(a, n, key);
    }

    if (position == -1) {
        printf("not found");
    } else {
        printf("%d", position);
    }

    return 0;
}
