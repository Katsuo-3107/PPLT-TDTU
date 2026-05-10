#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define PI 3.1415926535
#define EPS 1e-9

typedef struct {
    int bc;
    int bg;
    double con;
} KetQua;

int checkThoiTiet(const char *tg) {
    return strcmp(tg, "Rain") == 0 ||
           strcmp(tg, "Sun") == 0  ||
           strcmp(tg, "Cloud") == 0||
           strcmp(tg, "Fog") == 0  ||
           strcmp(tg, "Wind") == 0;
}

int checkInput(int n, int dc, int dg, int ld, const char *tg) {
    if (n < 1 || n > 2000) return 0;
    if (dc < 0 || dg < 0) return 0;
    if (dc == 0 && dg == 0) return 0;
    if (ld < 1 || ld > 600) return 0;
    return checkThoiTiet(tg);
}

double tinhNepBC(int dc) {
    if (dc <= 0) return 0;
    return dc * dc * sqrt((double)dc);
}

double tinhNepBG(int dg) {
    if (dg <= 0) return 0;
    return dg * dg * PI / 3.0;
}

int soLaBC(int dc) {
    if (dc <= 0) return 0;
    if (dc < 8) return 1;
    return 2;
}

int soLaBG(int dg) {
    if (dg <= 0) return 0;
    if (dg < 5) return 1;
    return 2;
}

int tinhMax(double nep, double nepBanh, int la, int laBanh) {
    if (nepBanh <= 0 || laBanh <= 0 || la <= 0 || nep < nepBanh - EPS)
        return 0;
    int theoNep = (int)((nep + EPS) / nepBanh);
    int theoLa  = la / laBanh;
    return theoNep < theoLa ? theoNep : theoLa;
}

long long sumUoc(int x) {
    if (x <= 1) return 0;
    long long s = 1;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            s += i;
            if (i * i != x) s += x / i;
        }
    }
    return s;
}

int isBanBe(int a, int b) {
    if (a <= 0 || b <= 0 || a == b) return 0;
    return sumUoc(a) == b && sumUoc(b) == a;
}

int isCP(long long v) {
    if (v < 0) return 0;
    long long r = (long long)(sqrt((double)v) + 0.5);
    return r * r == v;
}

int isFibo(int x) {
    long long n = x;
    return isCP(5*n*n + 4) || isCP(5*n*n - 4);
}

KetQua makeKQ(int bc, int bg, double con) {
    KetQua r;
    r.bc = bc;
    r.bg = bg;
    r.con = con < EPS ? 0 : con;
    return r;
}

// uuTien: 1 = uu tien chung, 0 = uu tien giay
KetQua tinh(int n, int dc, int dg, int ld, int uuTien) {
    double nep = n;
    int la   = ld;

    double nepC = tinhNepBC(dc);
    double nepG = tinhNepBG(dg);
    int laC = soLaBC(dc);
    int laG = soLaBG(dg);

    int bc = 0, bg = 0;

    if (uuTien) {
        bc   = tinhMax(nep, nepC, la, laC);
        nep -= bc * nepC;
        la  -= bc * laC;
        bg   = tinhMax(nep, nepG, la, laG);
        nep -= bg * nepG;
    } else {
        bg   = tinhMax(nep, nepG, la, laG);
        nep -= bg * nepG;
        la  -= bg * laG;
        bc   = tinhMax(nep, nepC, la, laC);
        nep -= bc * nepC;
    }

    return makeKQ(bc, bg, nep);
}

KetQua tinhWind(int n, int dc, int dg, int ld) {
    double nepC = tinhNepBC(dc);
    double nepG = tinhNepBG(dg);
    int laC = soLaBC(dc);
    int laG = soLaBG(dg);

    int maxBC = tinhMax(n, nepC, ld, laC);
    int maxBG = tinhMax(n, nepG, ld, laG);

    int bestBc = 0, bestBg = 0;
    double bestCon = n;

    for (int bc = 0; bc <= maxBC; bc++) {
        for (int bg = 0; bg <= maxBG; bg++) {
            if (bc * laC + bg * laG > ld) continue;
            double used = bc * nepC + bg * nepG;
            if (used > n + EPS) continue;

            double con = n - used;
            if (con < bestCon - EPS ||
               (fabs(con - bestCon) <= EPS && bg > bestBg) ||
               (fabs(con - bestCon) <= EPS && bg == bestBg && bc > bestBc)) {
                bestBc  = bc;
                bestBg  = bg;
                bestCon = con;
            }
        }
    }

    return makeKQ(bestBc, bestBg, bestCon);
}

KetQua tinhRain(int n, int dc, int dg, int ld) {
    double nepC = tinhNepBC(dc);
    double nepG = tinhNepBG(dg);
    int laC = soLaBC(dc);
    int laG = soLaBG(dg);

    int maxBC = tinhMax(n, nepC, ld, laC);
    int maxBG = tinhMax(n, nepG, ld, laG);

    int eqBc = -1;
    double eqCon = n;

    int bgGtBc = 0, gBc = 0, gBg = 0;
    double gCon = n;

    int altFound = 0, altBc = 0, altBg = 0, altDiff = 2147483647;
    double altCon = n;

    for (int bc = 0; bc <= maxBC; bc++) {
        for (int bg = 0; bg <= maxBG; bg++) {
            if (bc * laC + bg * laG > ld) continue;
            double used = bc * nepC + bg * nepG;
            if (used > n + EPS) continue;
            double con = n - used;

            if (bc == bg) {
                if (bc > eqBc || (bc == eqBc && con < eqCon - EPS)) {
                    eqBc = bc; eqCon = con;
                }
                continue;
            }

            if (bg > bc) {
                if (!bgGtBc || bc > gBc ||
                    (bc == gBc && bg > gBg) ||
                    (bc == gBc && bg == gBg && con < gCon - EPS)) {
                    bgGtBc = 1; gBc = bc; gBg = bg; gCon = con;
                }
                continue;
            }

            if (!altFound || con < altCon - EPS ||
                (fabs(con - altCon) <= EPS && abs(bc-bg) < altDiff) ||
                (fabs(con - altCon) <= EPS && abs(bc-bg) == altDiff && bc+bg > altBc+altBg) ||
                (fabs(con - altCon) <= EPS && abs(bc-bg) == altDiff && bc+bg == altBc+altBg && bc > altBc)) {
                altFound = 1; altBc = bc; altBg = bg;
                altDiff  = abs(bc-bg); altCon = con;
            }
        }
    }

    if (bgGtBc && (eqBc < 0 || laG == 1))
        return makeKQ(gBc, gBg, gCon);
    if (eqBc >= 0)
        return makeKQ(eqBc, eqBc, eqCon);
    if (bgGtBc)
        return makeKQ(gBc, gBg, gCon);
    if (altFound)
        return makeKQ(altBc, altBg, altCon);

    return makeKQ(0, 0, n);
}

KetQua tinhFog(int n, int dc, int dg, int ld) {
    int ndc = dc, ndg = dg;

    if (isFibo(dc) && isFibo(dg)) {
        ndc /= 2; ndg /= 2;
    } else {
        ndc *= 2; ndg *= 2;
    }

    if (ndc <= 0 && ndg <= 0) return makeKQ(0, 0, n);
    if (ndc <= 0) return tinh(n, ndc, ndg, ld, 0);
    if (ndg <= 0) return tinh(n, ndc, ndg, ld, 1);

    if (tinhNepBC(ndc) >= tinhNepBG(ndg))
        return tinh(n, ndc, ndg, ld, 1);
    return tinh(n, ndc, ndg, ld, 0);
}

int bonusSun(int dc, int ld) {
    int table[5][6] = {
        { 5,  7, 10, 12, 15, 20},
        {20,  5,  7, 10, 12, 15},
        {15, 20,  5,  7, 10, 12},
        {12, 15, 20,  5,  7, 10},
        {10, 12, 15, 20,  5,  7}
    };
    return table[ld % 5][dc % 6];
}

KetQua solve(int n, int dc, int dg, int ld, const char *tg, int fromSun);

KetQua solve(int n, int dc, int dg, int ld, const char *tg, int fromSun) {
    if (strcmp(tg, "Wind") == 0)  return tinhWind(n, dc, dg, ld);
    if (strcmp(tg, "Rain") == 0)  return tinhRain(n, dc, dg, ld);

    if (strcmp(tg, "Cloud") == 0) {
        if (isBanBe(n, ld)) return makeKQ(0, 0, n);
        return tinh(n, dc, dg, ld, fromSun ? 1 : 0);
    }

    if (strcmp(tg, "Fog") == 0) return tinhFog(n, dc, dg, ld);

    if (strcmp(tg, "Sun") == 0) {
        int bonus = bonusSun(dc, ld);
        int newN  = n + (int)(n * bonus / 100.0);
        int newLd = ld - bonus;

        char newTg[10];
        int sel = (dc + dg) % 3;
        if (sel == 0)      
            strcpy(newTg, "Rain");
        else if (sel == 1) 
            strcpy(newTg, "Wind");
        else               
            strcpy(newTg, "Cloud");

        if (newLd <= 0) return makeKQ(0, 0, newN);
        return solve(newN, dc, dg, newLd, newTg, 1);
    }

    return makeKQ(0, 0, n);
}

int main() {
    FILE *fi = fopen("input.txt",  "r");
    FILE *fo = fopen("output.txt", "w");
    if (!fi || !fo) return 1;

    int n, dc, dg, ld;
    char tg[16];

    int ok = fscanf(fi, "%d %d %d %d %15s", &n, &dc, &dg, &ld, tg);
    if (ok != 5 || !checkInput(n, dc, dg, ld, tg)) {
        fprintf(fo, "-1 -1 %d", n);
        fclose(fi); fclose(fo);
        return 0;
    }

    KetQua kq = solve(n, dc, dg, ld, tg, 0);
    fprintf(fo, "%d %d %.3f", kq.bc, kq.bg, kq.con);

    fclose(fi); fclose(fo);
    return 0;
}