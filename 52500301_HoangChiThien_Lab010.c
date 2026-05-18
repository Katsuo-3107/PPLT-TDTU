#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

float khoangCach(float xa, float ya, float xb, float yb) {
    return sqrt(pow(xa - xb, 2) + pow(ya - yb, 2));
}

float tinhDienTichTron(float chuvi) {
    float r = chuvi / (2 * PI);
    return PI * pow(r, 2);
}

void CheckNgayHopLe(int ngay, int thang, int nam) {
    if (nam < 1 || thang < 1 || thang > 12 || ngay < 1) {
        printf("Ngay khong hop le.\n");
        return;
    }
    
    int maxNgay;
    switch (thang) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            maxNgay = 31;
            break;
        case 4: case 6: case 9: case 11:
            maxNgay = 30;
            break;
        case 2:
            if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0)) {
                maxNgay = 29;
            } else {
                maxNgay = 28;
            }
            break;
        default:
            printf("Thang khong hop le.\n");
            return;
    }
    if (ngay > maxNgay) {
        printf("Ngay khong hop le.\n");
    } else {
        printf("Ngay hop le.\n");
    }
}

void kiemTraChuoiDoiXung(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            printf("0\n");
            return;
        }
    }
    printf("1\n");
}   

int DecToBinary(int n) {
    if (n == 0) {
        return 0;
    }
    return (n % 2) + 10 * DecToBinary(n / 2);
}

struct SinhVien 
{
    char MSSV[20];
    char HoTen[50];
    int DiemPPLT;
    int DiemĐSTT;
    int DiemToanTin;
    float DiemTB;
    char XepLoai[20];
};

int main() {
    float xa, ya, xb, yb;
    
    printf("1. Nhap toa do diem A (xa, ya): ");
    scanf("%f %f", &xa, &ya);
    
    printf("Nhap toa do diem B (xb, yb): ");
    scanf("%f %f", &xb, &yb);
    
    float distance = khoangCach(xa, ya, xb, yb);
    printf("Khoang cach giua diem A va diem B la: %.2f\n", distance);
    
    printf("2. Nhap chu vi hinh tron: ");

    float chuvi;
    scanf("%f", &chuvi);    

    float area = tinhDienTichTron(chuvi);
    printf("Dien tich hinh tron la: %.2f\n", area); 

    printf("3. Nhap ngay, thang, nam: ");

    int ngay, thang, nam;
    scanf("%d %d %d", &ngay, &thang, &nam);

    CheckNgayHopLe(ngay, thang, nam);   

    printf("4. Nhap chuoi: ");

    char str[100];
    scanf("%s", str);

    kiemTraChuoiDoiXung(str);

    printf("5. Nhap so nguyen: ");

    int n;
    scanf("%d", &n);

    int binary = DecToBinary(n);

    printf("So nhi phan: %d\n", binary);

    return 0;
}