#include <stdio.h>
#include <stdlib.h>

void swap(int *, int *);
int calc_pow(int, int);

int main( int argc, char* argv[] ) {
	int number;
	int power;
	int result;
	FILE *in_stream;

	if (argc == 1) {
		in_stream = stdin;
	} else {
		in_stream = fopen(argv[1], "r");
	}
	while (fscanf(in_stream, "%d %d", &number, &power) != EOF) {
		result = calc_pow(number, power);
		printf("%d to the power of %d is %d\n", number, power, result);
		swap(&number, &power);
		result = calc_pow(number, power);
		printf("%d to the power of %d is %d\n", number, power, result);
	}
		
	return 0;
}

void swap(int *a, int *b) {
	int tmp=NULL;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int calc_pow( int num, int pow ) {
	if ( pow == 0 ) {
		return 1;
	} 
	else {
		return num * calc_pow( num, pow-1 );
	} 
}
