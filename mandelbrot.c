#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

int isMandelbrot(double complex c){
	double complex z = 0.0 + 0.0 * I;
	for (int i = 0; i < 1000; i++){
		//printf("z: %.2lf + %.2lf\n", creal(z), cimag(z));
		//printf("result: %.2lf\n", sqrt(pow(creal(z), 2) + pow(cimag(z), 2)));
		z = z * z + c;
	}
	return sqrt(pow(creal(z), 2) + pow(cimag(z), 2)) - 2.0 < .00000000001;
}

int main(void){
	/*double complex a = -1.0 + 0.0 * I;
	double complex b = 0.0 + 1.0 * I;
	double complex c = -2.0 + 0.0 * I;
	double complex d = 3.0 + 0.0 * I;
	printf("%d\n", isMandelbrot(a));
	printf("%d\n", isMandelbrot(b));
	printf("%d\n", isMandelbrot(c));
	printf("%d\n", isMandelbrot(d));
	*/
	FILE *validPoints = fopen("mandelbrotPoints.txt", "w");
	for (double i = -2.1; i <= 2.1; i += .01){
		for (double j = -2.1; j <= 2.1; j += .01){
			double complex c = i + j * I;
			if (isMandelbrot(c)){
				printf("Point %.3lf + %.3lf: Yes\n", creal(c), cimag(c));
				fprintf(validPoints, "%.3lf + %.3lf\n", creal(c), cimag(c));
			} else {
				printf("Point %.3lf + %.3lf: No\n", creal(c), cimag(c));
			}
		}
	}
	fclose(validPoints);
	return 0;
}