#include "bct.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>

/*
 * Computes Marchiori and Latora's connectivity length for a weighted graph.
 */
double bct::connectivity_length_wei(const gsl_matrix* m) {
	if (safe_mode) check_status(m, SQUARE | WEIGHTED, "connectivity_length_wei");
	int N = m->size1;
	gsl_matrix* D = distance_wei(m);
	double sum = 0.0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			double value = gsl_matrix_get(D, i, j);
			if (gsl_finite(value) == 1 && fp_nonzero(value)) {
				sum += 1.0 / value;
			}
		}
	}
	gsl_matrix_free(D);
	if (fp_zero(sum)) {
		return GSL_POSINF;
	} else {
		return (double)(N * (N - 1)) / sum;
	}
}
