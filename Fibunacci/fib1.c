#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int sum_arrays (int * a, int * b, int an, int bn, int ** res);
int get_fib(int n, int ** res);
void print_usage();

int sum_arrays (int * a, int * b, int an, int bn, int ** res) {
	if (bn > an) {
		int * temp = b;
		b = a;
		a = temp;

		int t = an;
		an = bn;
		bn = t;
	}


	*res = calloc(an + 1, sizeof(int));

	if (!*res) {
		printf("Can't allocate memory!");
		exit(1);
	}

	int i;
	int naum = 0;

	int counter = an;
	int ca = an - 1;
	int cb= bn - 1;

	for (i = an - 1; i >= an - bn; i--) {
		int s = a[ca] + b[cb] + naum;
		ca -= 1;
		cb -= 1;

		if (s < 10) {
			(*res)[counter] = s;
			naum = 0;
		} else {
			(*res)[counter] = s % 10;
			naum = s / 10;
		}

		counter -= 1;
	}

	for (i = an - bn - 1; i >= 0; i--) {
		int s = a[i] + naum;

		if (s < 10) {
			(*res)[counter] = s;
			naum = 0;
		} else {
			(*res)[counter] = s % 10;
			naum = s / 10;
		}

		counter -= 1;
	}

	if (naum > 0){
		(*res)[counter] = naum;
		counter--;
	}

	if (counter == 0) {
		memmove(*res, (*res) + 1, an * sizeof(int));

		return an;
	}

	return an + 1;
}

int get_fib(int n, int ** res) {
	int * prev_prev = malloc(sizeof(int));

	if (!prev_prev) {
		printf("Can't allocate memory!");
		exit(1);
	}

	prev_prev[0] = 0;

	int * prev = malloc(sizeof(int));

	if (!prev) {
		printf("Can't allocate memory!");
		exit(1);
	}

	prev[0] = 1;



	int prevl = 1;
	int prev_prevl = 1;

	int current = 1;

	int l;
	while (current < n) {
		l = sum_arrays(prev, prev_prev, prevl, prev_prevl, res);
		current += 1;
		free(prev_prev);
		prev_prev = prev;
		prev = (*res);
		prev_prevl = prevl;
		prevl = l;
	}

	free(prev_prev);

	return l;
}

void print_usage() {
	printf("Usage: Fibunacci [n]\n");
	printf("n: Positive number. Default value is n = 100000\n");
}

int main(int argc, char ** argv) {
	int n = 1202;

	if (argc > 2) {
		print_usage();
		exit(1);
	}

	if (argc == 2) {
		char * option = argv[1];
		char * rem = NULL;

		long l = strtol(option, &rem, 10);

		if(errno != 0 || strlen(rem) > 0 || l <=0) {
			print_usage();
			exit(1);
		}

		if (l > 100000) {
			printf("The number is big. It will take time to make the calculation or you may not have enough memory for it. Are you sure you want to continue? (yes|no)");
			char answer[3];
			fgets(answer, 4, stdin);

			if (strcmp(answer, "yes") != 0) {
				exit(0);
			}
		}

		n = l;
	}

	int * res;
	int l = get_fib(n, &res);

	printf("fib(%d) has %d digits: ",n, l);

	int i;
	for (i = 0; i < l; i++) {
		printf("%d",res[i]);
	}

	printf("\n");
	free(res);

	return 0;
}
