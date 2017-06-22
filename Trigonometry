#include <stdio.h>
#define MAX_E 100
#define EPS 0.0000001

float bsearch(float key){
	float r = 1.0 + EPS, l = -EPS, m;
	char c;
	while(r - l > EPS){
		m = (r + l) / 2;
		//printf("%f %f %f. %f > %f\n", l, m, r, key, m*m);
		//scanf("%c", &c);
		if(key > m * m){
			l = m;
		}
		else{
			r = m;
		}
	} 
	return m;
}

int main(void) {
	int i, j;
	float x, sinx, numerator, denominator, temp;
	scanf("%f", &x);
	//printf("x is %f\n*******\n", x);
	sinx = 0;
	for(i = 0; i < MAX_E; i++){
		numerator = 1;
		denominator = 1;
		for(j = 1; j <= 2*i + 1; j++){
			numerator *= x;
			denominator *= j;
		}
		if(i % 2 == 1) numerator = -numerator;
		sinx += numerator / denominator;
		//printf("%f: %f / %f\n", sinx, numerator, denominator);
	}
	printf("sinx = %f, cosx = %f, tanx = %f", sinx, bsearch(1 - sinx * sinx), sinx / bsearch(1 - sinx * sinx));
	return 0;
}
