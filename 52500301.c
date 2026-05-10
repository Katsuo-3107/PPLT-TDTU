#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define PI 3.1415926535
#define EPS 1e-9

typedef struct {
    int bc;
    int bg;
    double nd;
} Result;

int laThoiTietHopLe(const char *weather) {
    return strcmp(weather, "Rain") == 0 ||
           strcmp(weather, "Sun") == 0 ||
           strcmp(weather, "Cloud") == 0 ||
           strcmp(weather, "Fog") == 0 ||
           strcmp(weather, "Wind") == 0;
}

int kiemTraInputBanDau(int n, int dc, int dg, int ld, const char *weather) {
    if (n < 1 || n > 2000) return 0;
    if (dc < 0 || dg < 0) return 0;
    if (dc == 0 && dg == 0) return 0;
    if (ld < 1 || ld > 600) return 0;
    return laThoiTietHopLe(weather);
}

double nepBanhChung(int dc) {
    if (dc <= 0) return 0;
    return dc * dc * sqrt((double)dc);
}

double nepBanhGiay(int dg) {
    if (dg <= 0) return 0;
    return dg * dg * PI / 3.0;
}

int laBanhChung(int dc) {
    if (dc <= 0) {
        return 0;
    }

    if (dc < 8) {
        return 1;
    } else {
        return 2;
    }
}

int laBanhGiay(int dg) {
    if (dg <= 0) {
        return 0;
    }

    if (dg < 5) {
        return 1;
    } else {
        return 2;
    }
}

int maxTheoTaiNguyen(double rice, double riceCake, int leaves, int leavesCake) {
    if (riceCake <= 0 || leavesCake <= 0 || leaves <= 0 || rice < riceCake - EPS) {
        return 0;
    }

    int theoNep = (int)((rice + EPS) / riceCake);
    int theoLa  = leaves / leavesCake;

    if (theoNep < theoLa) {
        return theoNep;
    } else {
        return theoLa;
    }
}

long long tongUoc(int x) {
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

int laCapBanBe(int a, int b) {
    if (a <= 0 || b <= 0 || a == b) return 0;
    return tongUoc(a) == b && tongUoc(b) == a;
}

int laChinhPhuong(long long v) {
    if (v < 0) return 0;
    long long r = (long long)(sqrt((double)v) + 0.5);
    return r * r == v;
}

int laFibo(int x) {
    long long n = x;
    return laChinhPhuong(5*n*n + 4) || laChinhPhuong(5*n*n - 4);
}

Result taoKQ(int bc, int bg, double nd) {
    Result r;
    r.bc = bc;
    r.bg = bg;
    r.nd = nd < EPS ? 0 : nd;
    return r;
}

Result giai(int n, int dc, int dg, int ld, int uuTienChung) {
    double riceRemain = n;
    int leavesRemain  = ld;

    double riceC = nepBanhChung(dc);
    double riceG = nepBanhGiay(dg);
    int laC = laBanhChung(dc);
    int laG = laBanhGiay(dg);

    int bc = 0, bg = 0;

    if (uuTienChung) {
        bc = maxTheoTaiNguyen(riceRemain, riceC, leavesRemain, laC);
        riceRemain -= bc * riceC;
        leavesRemain -= bc * laC;

        bg = maxTheoTaiNguyen(riceRemain, riceG, leavesRemain, laG);
        riceRemain -= bg * riceG;
    } else {
        bg = maxTheoTaiNguyen(riceRemain, riceG, leavesRemain, laG);
        riceRemain -= bg * riceG;
        leavesRemain -= bg * laG;

        bc = maxTheoTaiNguyen(riceRemain, riceC, leavesRemain, laC);
        riceRemain -= bc * riceC;
    }

    return taoKQ(bc, bg, riceRemain);
}

Result giaiWind(int n, int dc, int dg, int ld) {
    double riceC = nepBanhChung(dc);
    double riceG = nepBanhGiay(dg);

    int laC = laBanhChung(dc);
    int laG = laBanhGiay(dg);

    int maxBc = maxTheoTaiNguyen(n, riceC, ld, laC);
    int maxBg = maxTheoTaiNguyen(n, riceG, ld, laG);

    int bestBc = 0;
    int bestBg = 0;

    double bestLeft = n;

    for (int bc = 0; bc <= maxBc; bc++) {
        for (int bg = 0; bg <= maxBg; bg++) {

            int usedLeaves = bc * laC + bg * laG;
            if (usedLeaves > ld) continue;

            double usedRice = bc * riceC + bg * riceG;
            if (usedRice > n + EPS) continue;

            double left = n - usedRice;

            if (left < bestLeft - EPS ||
               (fabs(left - bestLeft) <= EPS && bg > bestBg) ||
               (fabs(left - bestLeft) <= EPS &&
                bg == bestBg && bc > bestBc)) {

                bestBc = bc;
                bestBg = bg;
                bestLeft = left;
            }
        }
    }

    return taoKQ(bestBc, bestBg, bestLeft);
}

Result giaiRain(int n, int dc, int dg, int ld) {
    double riceC = nepBanhChung(dc);
    double riceG = nepBanhGiay(dg);
    int laC = laBanhChung(dc);
    int laG = laBanhGiay(dg);

    int maxBc = maxTheoTaiNguyen(n, riceC, ld, laC);
    int maxBg = maxTheoTaiNguyen(n, riceG, ld, laG);

    int bestEqBc = -1;
    double bestEqLeft = n;

    int bestBgGtBcBc = 0;
    double bestBgGtBcLeft = n;
    int bestBgGtBcBg = 0;
    int bestBgGtBcFound = 0;

    int bestBc = 0, bestBg = 0, bestDiff = 2147483647;
    double bestLeft = n;
    int bestAltFound = 0;

    for (int bc = 0; bc <= maxBc; bc++) {
        for (int bg = 0; bg <= maxBg; bg++) {
            int usedLeaves = bc * laC + bg * laG;
            if (usedLeaves > ld) continue;

            double usedRice = bc * riceC + bg * riceG;
            if (usedRice > n + EPS) continue;

            double left = n - usedRice;

            if (bc == bg) {
                if (bc > bestEqBc || (bc == bestEqBc && left < bestEqLeft - EPS)) {
                    bestEqBc = bc;
                    bestEqLeft = left;
                }
                continue;
            }

            if (bg > bc) {
                if (!bestBgGtBcFound || bc > bestBgGtBcBc ||
                    (bc == bestBgGtBcBc && bg > bestBgGtBcBg) ||
                    (bc == bestBgGtBcBc && bg == bestBgGtBcBg && left < bestBgGtBcLeft - EPS)) {
                    bestBgGtBcFound = 1;
                    bestBgGtBcBc = bc;
                    bestBgGtBcBg = bg;
                    bestBgGtBcLeft = left;
                }
                continue;
            }

            if (!bestAltFound || left < bestLeft - EPS ||
                (fabs(left - bestLeft) <= EPS && abs(bc - bg) < bestDiff) ||
                (fabs(left - bestLeft) <= EPS && abs(bc - bg) == bestDiff &&
                 bc + bg > bestBc + bestBg) ||
                (fabs(left - bestLeft) <= EPS && abs(bc - bg) == bestDiff &&
                 bc + bg == bestBc + bestBg && bc > bestBc)) {
                bestAltFound = 1;
                bestBc = bc;
                bestBg = bg;
                bestDiff = abs(bc - bg);
                bestLeft = left;
            }
        }
    }

    if (bestBgGtBcFound && (bestEqBc < 0 || laG == 1)) {
        return taoKQ(bestBgGtBcBc, bestBgGtBcBg, bestBgGtBcLeft);
    }
    if (bestEqBc >= 0) {
        return taoKQ(bestEqBc, bestEqBc, bestEqLeft);
    }
    if (bestBgGtBcFound) {
        return taoKQ(bestBgGtBcBc, bestBgGtBcBg, bestBgGtBcLeft);
    }
    if (bestAltFound) {
        return taoKQ(bestBc, bestBg, bestLeft);
    }

    return taoKQ(0, 0, n);
}

Result giaiFog(int n, int dc, int dg, int ld) {
    int newDc = dc, newDg = dg;

    if (laFibo(dc) && laFibo(dg)) {
        newDc /= 2;
        newDg /= 2;
    } else {
        newDc *= 2;
        newDg *= 2;
    }

    if (newDc <= 0 && newDg <= 0) return taoKQ(0,0,n);
    if (newDc <= 0) return giai(n,newDc,newDg,ld,0);
    if (newDg <= 0) return giai(n,newDc,newDg,ld,1);

    if (nepBanhChung(newDc) >= nepBanhGiay(newDg))
        return giai(n,newDc,newDg,ld,1);

    return giai(n,newDc,newDg,ld,0);
}

int bonusSun(int dc, int ld) {
    int table[5][6] ={
        {5,7,10,12,15,20},
        {20,5,7,10,12,15},
        {15,20,5,7,10,12},
        {12,15,20,5,7,10},
        {10,12,15,20,5,7}
    };
    return table[ld%5][dc%6];
}

Result giaiTheoThoiTiet(int n, int dc, int dg, int ld, const char *weather, int fromSun) {
    if (strcmp(weather,"Wind")==0) return giaiWind(n,dc,dg,ld);
    if (strcmp(weather,"Rain")==0) return giaiRain(n,dc,dg,ld);

    if (strcmp(weather,"Cloud")==0) {
        if (laCapBanBe(n,ld)) return taoKQ(0,0,n);
        return giai(n,dc,dg,ld, fromSun ? 1 : 0);
    }

    if (strcmp(weather,"Fog")==0) return giaiFog(n,dc,dg,ld);

    if (strcmp(weather,"Sun")==0) {
        int bonus = bonusSun(dc,ld);
        int newN = n + (int)(n * bonus / 100.0);
        int newLd = ld - bonus;

        char newWeather[10];
        int sel = (dc+dg)%3;

        if (sel==0) strcpy(newWeather,"Rain");
        else if (sel==1) strcpy(newWeather,"Wind");
        else strcpy(newWeather,"Cloud");

        if (newLd <= 0) return taoKQ(0,0,newN);
        return giaiTheoThoiTiet(newN,dc,dg,newLd,newWeather,1);
    }

    return taoKQ(0,0,n);
}

int main() {
    FILE *fi = fopen("input.txt", "r");
    FILE *fo = fopen("output.txt", "w");

    if (fi == NULL || fo == NULL) {
        return 1;
    }

    int n, dc, dg, ld;
    char weather[16];

    int read = fscanf(fi, "%d %d %d %d %15s", &n, &dc, &dg, &ld, weather);

    if (read != 5 || !kiemTraInputBanDau(n, dc, dg, ld, weather)) {
        fprintf(fo, "-1 -1 %d", n);
        fclose(fi);
        fclose(fo);
        return 0;
    }

    Result kq = giaiTheoThoiTiet(n, dc, dg, ld, weather, 0);
    fprintf(fo, "%d %d %.3f", kq.bc, kq.bg, kq.nd);
    fclose(fi);
    fclose(fo);

    return 0;
}
