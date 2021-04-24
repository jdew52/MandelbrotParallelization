#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <omp.h>

int isMandelbrot(double complex c){
	double complex z = 0.0 + 0.0 * I;
	for (int i = 0; i < 1000; i++){
		z = z * z + c;
	}
	return sqrt(pow(creal(z), 2) + pow(cimag(z), 2)) - 2.0 < .00000000001;
}

int main(void){
	FILE *validPoints = fopen("mandelbrotPoints.txt", "w");
	int i;
	// inc is value to increment real/imaginary parts of c in loop
	double upperBound = 2.0, lowerBound = -2.0;
	double inc = 1.0;
	int limit = 0;
	for (double d = -2.0; d <= 2.0; d += inc){
		limit += 1;
	}
	// rl is the real part of the complex number, img is the imaginary part
	double rl = -2.0, img;
	// start stores the time in which the generation of points starts
	double start = omp_get_wtime();
	// The for loop iterates from 0 to number of points to generate
	// Both the real and imaginary part of the imaginary number are determined
	// from i.
	for (i = 0; i < limit*limit; i++){
		rl = lowerBound + (i / limit) * inc;
		img = lowerBound + (i % limit) * inc;
		double complex c = rl + img * I;
		if (isMandelbrot(c)){
			fprintf(validPoints, "%.3lf + %.3lf\n", creal(c), cimag(c));
		}
	}
	printf("Runtime: %lf\n", omp_get_wtime() - start);
	fclose(validPoints);
	return 0;
}