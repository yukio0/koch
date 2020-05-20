#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

struct Point
{
    double x, y;
};

int plotKoch(void)
{
    FILE *gp;
    gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set size ratio -1\n");
    fprintf(gp, "plot \'.kochPlot\' w l\n");

    pclose(gp); 
    return 0;
}

int koch(int n, FILE **fp, struct Point a, struct Point b)
{
    if (n == 0)
        return 0;

    struct Point s, t, u;
    double th = M_PI * 60.0 / 180.0;

    s.x = (2.0 * a.x + 1.0 * b.x) / 3.0;
    s.y = (2.0 * a.y + 1.0 * b.y) / 3.0;
    t.x = (1.0 * a.x + 2.0 * b.x) / 3.0;
    t.y = (1.0 * a.y + 2.0 * b.y) / 3.0;
    u.x = (t.x - s.x) * cos(th) - (t.y - s.y) * sin(th) + s.x;
    u.y = (t.x - s.x) * sin(th) + (t.y - s.y) * cos(th) + s.y;

    koch(n - 1,fp, a, s);
    fprintf(*fp,"%.8f %.8f\n", s.x, s.y);
    koch(n - 1,fp, s, u);
    fprintf(*fp,"%.8f %.8f\n", u.x, u.y);
    koch(n - 1,fp, u, t);
    fprintf(*fp,"%.8f %.8f\n", t.x, t.y);
    koch(n - 1,fp, t, b);
}

int main(void)
{
    int n;
    struct Point a, b;
    printf("step=");
    scanf("%d", &n);

    a.x = 0;
    a.y = 0;
    b.x = 10;
    b.y = 0;

    FILE *fp;
    fp = fopen("./.kochPlot", "w");
    fprintf(fp, "%.8f %.8f\n", a.x, a.y);
    koch(n,&fp, a, b);
    fprintf(fp, "%.8f %.8f\n", b.x, b.y);

    fclose(fp);

    plotKoch();
    return 0;
}