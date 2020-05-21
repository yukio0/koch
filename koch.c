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

    struct Point left, right, center;

    left.x = (2.0 * firstPoint.x + 1.0 * lastPoint.x) / 3.0;
    left.y = (2.0 * firstPoint.y + 1.0 * lastPoint.y) / 3.0;
    right.x = (1.0 * firstPoint.x + 2.0 * lastPoint.x) / 3.0;
    right.y = (1.0 * firstPoint.y + 2.0 * lastPoint.y) / 3.0;
    center.x = (right.x - left.x) * cos(sixtyDegrees) - (right.y - left.y) * sin(sixtyDegrees) + left.x;
    center.y = (right.x - left.x) * sin(sixtyDegrees) + (right.y - left.y) * cos(sixtyDegrees) + left.y;

    koch(n - 1, fp, firstPoint, left);
    fprintf(*fp, "%.8f %.8f\n", left.x, left.y);
    koch(n - 1, fp, left, center);
    fprintf(*fp, "%.8f %.8f\n", center.x, center.y);
    koch(n - 1, fp, center, right);
    fprintf(*fp, "%.8f %.8f\n", right.x, right.y);
    koch(n - 1, fp, right, lastPoint);

    return 0;
}

int main(void)
{
    int step;
    printf("step=");
    scanf("%d", &step);

    struct Point firstPoint, lastPoint;
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