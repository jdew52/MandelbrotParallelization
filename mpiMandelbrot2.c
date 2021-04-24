#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <mpi.h>

int isMandelbrot(double complex c){
	double complex z = 0.0 + 0.0 * I;
	for (int i = 0; i < 1000; i++){
		z = z * z + c;
	}
	return sqrt(pow(creal(z), 2) + pow(cimag(z), 2)) - 2.0 < .00000000001;
}

int main(int argc, char *argv[]){
	FILE *validPoints = fopen("mandelbrotPoints.txt", "w");
	int i, myid, numprocs;
	// inc is value to increment real/imaginary parts of c in loop
	double upperBound = 2.0, lowerBound = -2.0;
	double inc = .001;
	MPI_Status status;
    /* Initialize MPI and get number of processes and my number or rank*/
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	int limit = 0;
	double start;
	if (myid == 0){
		for (double d = -2.0; d <= 2.0; d += inc){
			limit += 1;
		}
		for (i = 1; i < numprocs; i++){
			MPI_Send(&limit, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		// start stores the time in which the generation of points starts
		start = MPI_Wtime();
	} else {
		MPI_Recv(&limit, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	}
	// rl is the real part of the complex number, img is the imaginary part
	double rl, img;
	// The for loop iterates from 0 to number of points to generate
	// Both the real and imaginary part of the imaginary number are determined
	// from i.
	int chunkSize = (limit * limit) / numprocs;
	if (myid == numprocs - 1){
		for (i = myid*chunkSize; i < limit*limit; i++){
			rl = lowerBound + (i / limit) * inc;
			img = lowerBound + (i % limit) * inc;
			double complex c = rl + img * I;
			if (isMandelbrot(c)){
				fprintf(validPoints, "%.3lf + %.3lf\n", creal(c), cimag(c));
			}
		}
	} else {
		for (i = myid*chunkSize; i < (myid+1)*chunkSize; i++){
			rl = lowerBound + (i / limit) * inc;
			img = lowerBound + (i % limit) * inc;
			double complex c = rl + img * I;
			if (isMandelbrot(c)){
				fprintf(validPoints, "%.3lf + %.3lf\n", creal(c), cimag(c));
			}
		}
	}
	if (myid == 0){
		printf("Runtime: %lf\n", MPI_Wtime() - start);
	}
	MPI_Finalize();
	fclose(validPoints);
	return 0;
}