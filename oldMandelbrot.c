#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int isMandelbrot(double complex c){
	double complex z = 0.0 + 0.0 * I;
	for (int i = 0; i < 1000; i++){
		z = z * z + c;
	}
	return sqrt(pow(creal(z), 2) + pow(cimag(z), 2)) < 2.0;
}

int main(void){
	FILE *validPoints = fopen("mandelbrotPoints.txt", "w");
	double i, j;
	// inc is value to increment real/imaginary parts of c in loop
	double upperBound = 2.0, lowerBound = -2.0;
	double inc = .001;
	// i counts goes through the number of iterations necessary to get from -2 to 2 with the given inc value
	double start = omp_get_wtime();
	for (i = lowerBound; i <= upperBound; i += inc){
		img = -2.0;
		for (j = lowerBound; j <= upperBound; j += inc){
			double complex c = i + j * I;
			if (isMandelbrot(c)){
				fprintf(validPoints, "%.3lf + %.3lf\n", creal(c), cimag(c));
			}
		}
	}
	printf("Runtime: %lf\n", omp_get_wtime() - start);
	fclose(validPoints);
	return 0;
}