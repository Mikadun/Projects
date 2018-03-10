#include <stdio.h>
#include <math.h>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define EPS 0.000001
  
int main(){
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    double r, x1, y1, dx1, dy1, x2, y2, dx2, dy2;
    double d, D, dSx, dSy, dUx, dUy, a, b, c;
    fscanf(fin, "%lf", &r);
    d = 2 * r;
    fscanf(fin, "%lf %lf %lf %lf", &x1, &y1, &dx1, &dy1);
    fscanf(fin, "%lf %lf %lf %lf", &x2, &y2, &dx2, &dy2);
    dSx = x1 - x2;
    dSy = y1 - y2;
    dUx = dx1 - dx2;
    dUy = dy1 - dy2;
    a = dUx * dUx + dUy * dUy;
    if(a == 0){
        fprintf(fout, "-1");
        return 0;
    }
    b = 2 * (dSx * dUx + dSy * dUy);
    c = dSx * dSx + dSy * dSy - d * d;
    D = b * b - 4 * a * c;
    if(D < 0){
        fprintf(fout, "-1");
        return 0;
    }
    double root1, root2;
    root1 = (-b + sqrt(D)) / (2 * a);
    root2 = (-b - sqrt(D)) / (2 * a);
    if(D == 0 && root1 > EPS){
        fprintf(fout, "%lf", root1);
        return 0;
    }
    if(root1 < EPS){
        if(root2 < EPS){
            fprintf(fout, "-1");
        } else {
            fprintf(fout, "%.4lf", root2);
        }
    } else if(root2 < EPS){
        fprintf(fout, "%.4lf", root1);
    } else {
        fprintf(fout, "%.4lf", MIN(root1, root2));
    }
}
