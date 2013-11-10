#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <complex.h>
#include "Matrix.h"

#include "MyTypes.h"

/**
 *Real matrix methods.
 */
#define TYPE Real
#define MANGLE(x) rmat##x
#include "Matrix.tc"
#undef TYPE
#undef MANGLE


/**
 *Complex matrix methods.
 */
#define TYPE Complex
#define MANGLE(x) cmat##x
#include "Matrix.tc"
#undef TYPE
#undef MANGLE


/**
 *Index matrix methods.
 */
#define TYPE Index
#define MANGLE(x) imat##x
#include "Matrix.tc"
#undef TYPE
#undef MANGLE
