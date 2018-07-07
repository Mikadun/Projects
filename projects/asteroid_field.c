#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100
#define sqr(x) ((x) * (x))

typedef struct {
	double x, y;
} Point;

typedef struct {
	Point center;
	double r;
} Circle;

typedef struct {
	double alpha, beta;
} Angles;

Circle circles[MAX_SIZE];
Angles angles[2 * MAX_SIZE];
int angles_size = 0;

void add_angles(double alpha, double beta){
	angles[angles_size].alpha = alpha;
	angles[angles_size].beta = beta;
	angles_size++;
}

Point P0;

Point get_vector(Point a, Point b){
	Point temp;
	temp.x = b.x - a.x;
	temp.y = b.y - a.y;
	return temp;
}

double get_angle_by_tan(double x, double y){
	return atan(y / x);
}

double get_angle_by_sin(double x, double y){
    return asin(y / x);
}

double get_vector_len(Point v){
	return sqrt(sqr(v.x) + sqr(v.y));
}

void swap_angles(Angles *a, Angles *b){
	Angles temp = *a;
	*a = *b;
	*b = temp;
}

void beta_sort(){
	int i, j;
	for(i = 1; i < angles_size; i++){
		int j = i;
		while(j > 0 && angles[j].alpha == angles[j - 1].alpha && angles[j].beta < angles[j - 1].beta){
			swap_angles(&(angles[j]), &(angles[j - 1]));
			j--;
		}
	}
}

double get_alpha(Point v){
	double alpha = get_angle_by_tan(v.x, v.y);
	if(v.x < 0 && v.y >= 0) alpha = M_PI + alpha;
	if(v.x < 0 && v.y < 0) alpha = M_PI + alpha;
	if(v.x >= 0 && v.y < 0) alpha = 2 * M_PI + alpha;
	return alpha;
}

int cmpfunc(const void *a, const void *b){
	double A = ((Angles *)a)->alpha;
	double B = ((Angles *)b)->alpha;
	if(A > B) return 1;
	if(A == B) return 0;
	if(A < B) return -1;
}

double find_angle(){
	int i = 0;
	double gamma;
	if(angles[i].alpha <= 0){
		double beta = angles[i].beta;
		while(i < angles_size - 1 && beta >= angles[i + 1].alpha){
			if(angles[i + 1].beta > beta) beta = angles[i + 1].beta;
			i++;
		}
		gamma = 0.5 * (beta + angles[i + 1].alpha);
	} else gamma = 0.5 * angles[i].alpha;
	return gamma;
}

void count_angles(int i){
	double d = get_vector_len(get_vector(P0, circles[i].center));
	double alpha = get_alpha(get_vector(P0, circles[i].center));
	double beta = get_angle_by_sin(d, circles[i].r);
	alpha -= beta;
	if(alpha <= 0){
		alpha += 2 * M_PI;
		add_angles(alpha, 2 * M_PI);
		beta *= 2;
		beta += alpha;
		add_angles(0.0, beta - 2 * M_PI);
	} else {
		beta *= 2;
		beta += alpha;
		add_angles(alpha, beta);
	}
}

int main(){
	FILE *fin = fopen("input.txt", "r");
	FILE *fout = fopen("output.txt", "w");
	int i, j, n;
	fscanf(fin, "%lf %lf", &P0.x, &P0.y);
	fscanf(fin, "%d", &n);
	for(i = 0; i < n; i++){
		fscanf(fin, "%lf %lf %lf", &circles[i].center.x, &circles[i].center.y, &circles[i].r);
	}
	for(i = 0; i < n; i++){
		count_angles(i);
	}
	qsort(angles, angles_size, sizeof(Angles), cmpfunc);
	beta_sort();
	double gamma = find_angle();
	
	double x, y;
	x = 1.0;
	if(0.5 * M_PI <= gamma && gamma <= 1.5 * M_PI) x *= -1;
	y = x * tan(gamma);
	fprintf(fout, "%.5lf %.5lf", x + P0.x, y + P0.y);
}
