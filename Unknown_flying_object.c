#include <stdio.h>
#include <math.h>
#define to_rad(x) (x * M_PI / 180)

double tan(double x){
	return sin(x) / cos(x);
}

int is_correct(double a, double b){
	return (a < b && b < 180) || (a > b && b > 180);
}

int main(){
	FILE *fin = fopen("input.txt", "r");
	FILE *fout = fopen("output.txt", "w");
	double a, b;
	fscanf(fin, "%lf %lf", &a, &b);
	if(is_correct(a, b)){
		b = 180 - b;
		a = to_rad(a);
		b = to_rad(b);
		double x = 100 * tan(b) / (tan(b) + tan(a));
		double y = x * tan(a);
		fprintf(fout, "%.4lf %.4lf", x, y);
	}
	else{
		fprintf(fout, "0 0");
	}

}
