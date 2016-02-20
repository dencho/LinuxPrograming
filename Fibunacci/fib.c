#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum (int * a, int * b, int lena, int lenb, int ** res) {
	int size = lena > lenb ? lena : lenb;
	*res = calloc(size + 1, sizeof(int));

	if (!*res) {
		printf("Can't allocate memory!");
		exit(1);
	}

	int i;
	int counter = size;
	int naum = 0;
	int ca = lena - 1;
	int cb= lenb - 1;

	for (i = size - 1; i >= abs(lena - lenb); i--) {
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

	for (i = abs(lena - lenb) - 1; i >= 0; i--) {
		if (lena > lenb) {
			int s = a[i] + naum;

			if (s < 10) {
				(*res)[counter] = s;
				naum = 0;
			} else {
				(*res)[counter] = s % 10;
				naum = s / 10;
			}

			counter -= 1;
		} else {
			int s = b[i] + naum;

			if (s < 10) {
				(*res)[counter] = s;
				naum = 0;
			} else {
				(*res)[counter] = s % 10;
				naum = s / 10;
			}

			counter -= 1;
		}
	}

	if (naum > 0){
		(*res)[counter] = naum;
		counter--;
	}

	if (counter == 0) {
		memmove(*res, (*res) + 1, size * sizeof(int));
		return size;
	}

	return size + 1;
}

int get_fib(int n, int ** res) {
	int * prev = malloc(sizeof(int));
	prev[0] = 1;
	int * prev_prev = malloc(sizeof(int));
	prev_prev[0] = 0;

	int prevl = 1;
	int prev_prevl = 1;

	int current = 1;

	int l;
	while (current < n) {
		l = sum(prev, prev_prev, prevl, prev_prevl, res);
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

int main() {
	int n = 100000;
	int * res;

	int l = get_fib(n, &res);

	int i;

	printf("%d: ",l);

	for (i = 0; i < l; i++) {
		printf("%d",res[i]);
	}

	free(res);

	return 0;
}
