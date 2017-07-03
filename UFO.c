#include <stdio.h>
#include <math.h>

int main(){
	double A, B;
	scanf("%lf %lf", &A, &B);
	B = 180 - B;
	double x = (tan(B) * 100) / (tan(B) + tag(A));
	double y = tan(A) * x;
	printf("%lf %lf", x, y);
}
