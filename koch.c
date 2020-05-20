#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846
double sixtyDegrees = M_PI * 60.0 / 180.0;

struct Point
{
    double x, y;
};

int plotKoch(int step)
{
    FILE *gp;
    gp = popen("gnuplot -persist", "w");

    fprintf(gp, "set size ratio -1\n");
    fprintf(gp, "set noborder\n");
    fprintf(gp, "set nozeroaxis\n");
    fprintf(gp, "set nogrid\n");
    fprintf(gp, "set noxzeroaxis\n");
    fprintf(gp, "set noyzeroaxis\n");
    fprintf(gp, "set noxtics\n");
    fprintf(gp, "set noytics\n");
    fprintf(gp, "set key\n");
    fprintf(gp, "plot \'.kochPlot\' w l title \'step=%d\'\n", step);

    pclose(gp);
    return 0;
}

int koch(int n, FILE **fp, struct Point firstPoint, struct Point lastPoint)
{
    if (n == 0)
        return 0;

    struct Point s, t, u;
    

    s.x = (2.0 * firstPoint.x + 1.0 * lastPoint.x) / 3.0;
    s.y = (2.0 * firstPoint.y + 1.0 * lastPoint.y) / 3.0;
    t.x = (1.0 * firstPoint.x + 2.0 * lastPoint.x) / 3.0;
    t.y = (1.0 * firstPoint.y + 2.0 * lastPoint.y) / 3.0;
    u.x = (t.x - s.x) * cos(sixtyDegrees) - (t.y - s.y) * sin(sixtyDegrees) + s.x;
    u.y = (t.x - s.x) * sin(sixtyDegrees) + (t.y - s.y) * cos(sixtyDegrees) + s.y;

    koch(n - 1, fp, firstPoint, s);
    fprintf(*fp, "%.8f %.8f\n", s.x, s.y);
    koch(n - 1, fp, s, u);
    fprintf(*fp, "%.8f %.8f\n", u.x, u.y);
    koch(n - 1, fp, u, t);
    fprintf(*fp, "%.8f %.8f\n", t.x, t.y);
    koch(n - 1, fp, t, lastPoint);
}

int main(void)
{
    int step;
    struct Point firstPoint, lastPoint;
    printf("step=");
    scanf("%d", &step);

    firstPoint.x = 0;
    firstPoint.y = 0;
    lastPoint.x = 10;
    lastPoint.y = 0;

    FILE *fp;
    fp = fopen("./.kochPlot", "w");
    fprintf(fp, "%.8f %.8f\n", firstPoint.x, firstPoint.y);
    koch(step, &fp, firstPoint, lastPoint);
    fprintf(fp, "%.8f %.8f\n", lastPoint.x, lastPoint.y);

    fclose(fp);

    plotKoch(step);
    return 0;
}