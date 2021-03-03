#include <iostream>
#include <cmath>
#include "mpi.h"

using namespace std;

float f(float x) {
	return sin(x);
}

float simpson(float l, float r) {
	return (r - l) * (f(l) + 4 * f((l + r) / 2) + f(r)) / 6;
}

int main(int argc, char** argv) {
	int size, rank, n = 50;
	int borders[2];
	float a = 2, b = 10, h = (b - a) / n, sum = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Status status;

	if (rank == 0) {
		for (int i = 1; i < size; i++) {
			borders[0] = (i - 1) * (n / size);
			borders[1] = i * (n / size);
			MPI_Send(borders, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
		}

		float local_sum = 0;
		for (int i = 1; i < size; i++) {
			MPI_Recv(&local_sum, 1, MPI_FLOAT, i, 1, MPI_COMM_WORLD, &status);
			sum += local_sum;
		}

		// add leftover sum
		int left = (size - 1) * (n / size);
		sum += simpson(a + left * h, b);
		cout << "integral is " << sum << endl;
	}
	else {
		MPI_Recv(&borders, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		for (int i = borders[0]; i < borders[1]; i++)
			sum += simpson(a + i * h, a + (i + 1) * h);
		MPI_Send(&sum, 1, MPI_FLOAT, 0, 1, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
