#include <bct/bct.h>
#include "bct_test.h"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <octave/oct.h>

DEFUN_DLD(motif4struct_bin_cpp, args, , "Wrapper for C++ function.") {
	bct::set_motif_mode(bct::SPORNS);
	if (args.length() != 1) {
		return octave_value_list();
	}
	Matrix A = args(0).matrix_value();
	if (!error_state) {
		gsl_matrix* A_gsl = bct_test::to_gslm(A);
		gsl_vector* f;
		gsl_matrix* F = bct::motif4struct_bin(A_gsl, &f);
		octave_value_list ret;
		ret(0) = octave_value(bct_test::from_gsl(f));
		ret(1) = octave_value(bct_test::from_gsl(F));
		gsl_matrix_free(A_gsl);
		gsl_vector_free(f);
		gsl_matrix_free(F);
		return ret;
	} else {
		return octave_value_list();
	}
}