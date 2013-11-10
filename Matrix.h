#ifndef MATRIX_H_
#define MATRIX_H_

#include "MyTypes.h"

/********************************/
/*                              */
/* Templated struct definitions */
/*                              */
/********************************/

/**
 *Matrix of real values.
 */
#define TYPE Real
#define MANGLE(x) rmat##x
#include "Matrix.th"
#undef TYPE
#undef MANGLE


/**
 *Matrix of complex values.
 */
#define TYPE Complex
#define MANGLE(x) cmat##x
#include "Matrix.th"
#undef TYPE
#undef MANGLE

/**
 *Matrix of indices.
 */
#define TYPE Index
#define MANGLE(x) imat##x
#include "Matrix.th"
#undef TYPE
#undef MANGLE


/*************************/
/*                       */
/* Overloaded functions. */
/*                       */
/*************************/

/**
 *Frees matrix.
 */
#define Mat_free(X) _Generic((X), \
		rmat*: rmat_free, \
		cmat*: cmat_free, \
		imat*: imat_free)(X)

/**
 *Writes matrix to binary file.
 */
#define Mat_bin_write(X,Y) _Generic((X), \
		rmat*: rmat_bin_write, \
		cmat*: cmat_bin_write, \
		imat*: imat_bin_write)(X,Y)

/**
 *Set matrix entry.
 */
#define Mat_set(X,Y,Z,U) _Generic((X),\
		rmat*: rmat_set,\
		cmat*: cmat_set,\
		imat*: imat_set)(X,Y,Z,U)

/**
 *Get matrix entry.
 */
#define Mat_get(X,Y,Z) _Generic((X),\
		rmat*: rmat_get,\
		cmat*: cmat_get,\
		imat*: imat_get)(X,Y,Z)

/**
 * Print to stdout.
 */
#define Mat_print(X) _Generic((X),\
		rmat*: rmat_print,\
		cmat*: cmat_print,\
		imat*: imat_print)(X)

#endif
