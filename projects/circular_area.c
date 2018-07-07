#include <stdio.h>
#include <math.h>
#define q(x) ((x)*(x))
 
void swap(double *a, double *b){
    double *temp = a;
    a = b;
    b = temp;
}
 
int main(){
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    double x1, y1, r1, x2, y2, r2;
    fscanf(fin, "%lf %lf %lf", &x1, &y1, &r1);
    fscanf(fin, "%lf %lf %lf", &x2, &y2, &r2);
    double d, h1, h2, alpha, beta, S;
    d = sqrt(q(x1 - x2) + q(y1 - y2));
    if(r1 < r2) swap(&r1, &r2);
    if(r1 >= r2 + d){
        S = M_PI * q(r2);
    } else if(r1 + r2 <= d){
        S = 0.0;
    } else {
        h1 = (q(r1) - q(r2) + q(d)) / (2*d); 
        if(h1 < d){
            h2 = d - h1;
            alpha = acos(h1 / r1) * 2;
            beta = acos(h2 / r2) * 2;
            S = 0.5 * (q(r1) * (alpha - sin(alpha)) + q(r2) * (beta - sin(beta)));
        } else {
            h2 = h1 - d;
            alpha = acos(h1 / r1) * 2;
            beta = acos(h2 / r2) * 2;
            S = 0.5 * q(r1) * (alpha - sin(alpha)) + M_PI * q(r2) - 0.5 * q(r2) * (beta - sin(beta));
        }
    }
    fprintf(fout, "%.2lf", S);
}
