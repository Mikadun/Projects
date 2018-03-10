#include <stdio.h>
 
int main(){
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", " w");
    double x, y, Ux, Uy, t;
    int cath;
    fscanf(fin, "%d", &cath);
    fscanf(fin, "%lf %lf", &x, &y);
    fscanf(fin, "%lf %lf %lf", &Ux, &Uy, &t);
    x += t * Ux;
    y += t * Uy;
    int x_inversion = floor(x / cath);
    int y_inversion = floor(y / cath);
    x -= x_inversion * cath;
    y -= y_inversion * cath;
    if(x_inversion % 2 != 0)
        x = cath - x;
    if(y_inversion % 2 != 0)
        y = cath - y;
    if(x + y > cath){
        double temp = x;
        x = cath - y;
        y = cath - temp;
    }
    fprintf(fout, "%.3lf %.3lf", x, y);
    return 0;
}
