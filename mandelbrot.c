#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <time.h>

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
	double inc = .001;
	int limit = 0;
	// try to find an elegant O(1) method for limit
	//int test = (upperBound - lowerBound) / inc;
	for (double d = -2.0; d <= 2.0; d += inc){
		limit += 1;
	}
	// rl is the real part of the complex number
	double rl = -2.0;
	clock_t start, end;
	start = clock();
	// i counts goes through the number of iterations necessary to get from -2 to 2 with the given inc value
	for (i = 0; i <= limit; i++){
		for (double j = lowerBound; j <= upperBound; j += inc){
			double complex c = rl + j * I;
			if (isMandelbrot(c)){
				//printf("Point %.3lf + %.3lf: Yes\n", creal(c), cimag(c));
				fprintf(validPoints, "%.3lf + %.3lf\n", creal(c), cimag(c));
			} /*else {
				printf("Point %.3lf + %.3lf: No\n", creal(c), cimag(c));
			} */
		}
		rl += inc;
	}
	printf("Runtime: %lf\n", ((double)clock() - start) / CLOCKS_PER_SEC);
	//printf("Limit: %d\n", limit);
	fclose(validPoints);
	return 0;
}