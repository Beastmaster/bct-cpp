#include "bct.h"
#include <gsl/gsl_matrix.h>

/*
 * Computes density for a directed graph.  Connection weights are ignored.
 */
double bct::density_dir(const gsl_matrix* CIJ) {
	if (safe_mode) check_status(CIJ, DIRECTED, "density_dir");
	if (CIJ->size1 != CIJ->size2) throw size_exception();
	
	// N = size(CIJ,1);
	int N = CIJ->size1;
	
	// K = nnz(CIJ);
	int K = nnz(CIJ);
	
	// kden = K/(N^2-N);
	return (double)K / (double)(N * N - N);
}
