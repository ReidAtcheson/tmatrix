/************************/
/*                      */
/* Matrix method tests. */
/*                      */
/************************/

#include "Matrix/Matrix.h"
#include "MyTypes.h"
#include <complex.h>
#include <stdlib.h>


#include "CUnit/Basic.h"
static const char filename[] = "test.bin";

void test_alloc(void);
void test_bin_IO(void);
void test_mat_getset(void);

int mat_init(void);
int mat_cleanup(void);


/**
 *Placeholder init/cleanups. Not relevant here.
 */
int mat_init(void){return 0;}
int mat_cleanup(void){return 0;}




void test_alloc(void){
	/*Test typical case:*/
	{
		int nrows=50;
		int ncols=250;
		rmat* real_matrix = rmat_alloc(nrows,ncols);
		cmat* complex_matrix = cmat_alloc(nrows,ncols);
		imat* index_matrix = imat_alloc(nrows,ncols);

		CU_ASSERT(real_matrix != NULL);
		CU_ASSERT(complex_matrix != NULL);
		CU_ASSERT(index_matrix != NULL);

		CU_ASSERT(real_matrix->data != NULL);
		CU_ASSERT(complex_matrix->data != NULL);
		CU_ASSERT(index_matrix->data != NULL);


		CU_ASSERT(real_matrix->nrows == nrows);
		CU_ASSERT(complex_matrix->nrows == nrows);
		CU_ASSERT(index_matrix->nrows == nrows);

		CU_ASSERT(real_matrix->ncols == ncols);
		CU_ASSERT(complex_matrix->ncols == ncols);
		CU_ASSERT(index_matrix->ncols == ncols);


		/*Should succeed..*/
		CU_ASSERT(EXIT_SUCCESS == Mat_free(real_matrix));
		CU_ASSERT(EXIT_SUCCESS == Mat_free(complex_matrix));
		CU_ASSERT(EXIT_SUCCESS == Mat_free(index_matrix));
	}

	/*Test fail cases.*/
	{
		int nrows=0;
		int ncols=250;
		rmat* real_matrix = rmat_alloc(nrows,ncols);
		cmat* complex_matrix = cmat_alloc(nrows,ncols);
		imat* index_matrix = imat_alloc(nrows,ncols); 
		CU_ASSERT(real_matrix == NULL);
		CU_ASSERT(complex_matrix == NULL);
		CU_ASSERT(index_matrix == NULL);

		/*Free should now alert us.*/
		CU_ASSERT(EXIT_SUCCESS != Mat_free(real_matrix));
		CU_ASSERT(EXIT_SUCCESS != Mat_free(complex_matrix));
		CU_ASSERT(EXIT_SUCCESS != Mat_free(index_matrix));
	
	}

	{
		int nrows=53;
		int ncols=0;
		rmat* real_matrix = rmat_alloc(nrows,ncols);
		cmat* complex_matrix = cmat_alloc(nrows,ncols);
		imat* index_matrix = imat_alloc(nrows,ncols); 
		CU_ASSERT(real_matrix == NULL);
		CU_ASSERT(complex_matrix == NULL);
		CU_ASSERT(index_matrix == NULL);

		/*Should fail..*/
		CU_ASSERT(0 != Mat_free(real_matrix));
		CU_ASSERT(0 != Mat_free(complex_matrix));
		CU_ASSERT(0 != Mat_free(index_matrix));
	
	}

	{
		int nrows=0;
		int ncols=0;
		rmat* real_matrix = rmat_alloc(nrows,ncols);
		cmat* complex_matrix = cmat_alloc(nrows,ncols);
		imat* index_matrix = imat_alloc(nrows,ncols); 
		CU_ASSERT(real_matrix == NULL);
		CU_ASSERT(complex_matrix == NULL);
		CU_ASSERT(index_matrix == NULL);


		/*Should fail..*/
		CU_ASSERT(EXIT_SUCCESS != Mat_free(real_matrix));
		CU_ASSERT(EXIT_SUCCESS != Mat_free(complex_matrix));
		CU_ASSERT(EXIT_SUCCESS != Mat_free(index_matrix));
	
	}


}


void test_bin_IO(void)
{

	int nrows = 253;
	int ncols = 161;
	
	/*Real case.*/
	{
		int i,j;
		rmat* real_matrix = rmat_alloc(nrows,ncols);
		for(i=1;i<=nrows;i++)
			for(j=1;j<=ncols;j++)
				Mat_set(real_matrix,i,j,(Real)i+(Real)j);


		CU_ASSERT(EXIT_SUCCESS == Mat_bin_write(real_matrix,filename));
		rmat* test = rmat_bin_read(filename);
		CU_ASSERT(NULL != test);


		for(i=1;i<=nrows;i++)
			for(j=1;j<=ncols;j++)
				CU_ASSERT(Mat_get(test,i,j)==(Real)i+(Real)j);


		CU_ASSERT(EXIT_SUCCESS == Mat_free(real_matrix));
		CU_ASSERT(EXIT_SUCCESS == Mat_free(test));

	}

	/*Complex case.*/
	{
		int i,j;
		cmat* complex_matrix = cmat_alloc(nrows,ncols);
		for(i=1;i<=nrows;i++)
			for(j=1;j<=ncols;j++)
				Mat_set(complex_matrix,i,j,(Real)i+(Complex) _Complex_I*j);

		CU_ASSERT(EXIT_SUCCESS == Mat_bin_write(complex_matrix,filename));
		cmat* test = cmat_bin_read(filename);
		CU_ASSERT(NULL != test);



		for(i=1;i<=nrows;i++)
			for(j=1;j<=ncols;j++)
				CU_ASSERT(Mat_get(test,i,j)==(Real)i+(Complex)_Complex_I*j);

		CU_ASSERT(EXIT_SUCCESS==Mat_free(complex_matrix));
		Mat_free(test);
	}

	/*Index case.*/
	{
	int i,j;
	imat* index_matrix = imat_alloc(nrows,ncols);
	for(i=1;i<=nrows;i++)
		for(j=1;j<=ncols;j++)
			Mat_set(index_matrix,i,j,(Index)i+(Index)j);

	CU_ASSERT( EXIT_SUCCESS==Mat_bin_write(index_matrix,filename) );
	imat* test = imat_bin_read(filename);
	CU_ASSERT(NULL != test);

	for(i=1;i<=nrows;i++)
		for(j=1;j<=ncols;j++)
			CU_ASSERT(Mat_get(test,i,j)==(Index)i+(Index)j);


		Mat_free(index_matrix);
		CU_ASSERT(EXIT_SUCCESS==Mat_free(test));
	}



}


void test_mat_getset(void){
	int nrows = 253;
	int ncols = 161;
	
	/*Real case.*/
	{
		int i,j;
		rmat* real_matrix = rmat_alloc(nrows,ncols);
		for(i=1;i<=nrows;i++)
			for(j=1;j<=ncols;j++)
				Mat_set(real_matrix,i,j,(Real)i+(Real)j);

		for(i=1;i<=nrows;i++)
			for(j=1;j<=ncols;j++)
				CU_ASSERT(Mat_get(real_matrix,i,j)==(Real)i+(Real)j);

		Mat_free(real_matrix);

	}

	/*Complex case.*/
	{
		int i,j;
		cmat* complex_matrix = cmat_alloc(nrows,ncols);
		for(i=1;i<=nrows;i++)
			for(j=1;j<=ncols;j++)
				Mat_set(complex_matrix,i,j,(Real)i+(Complex) _Complex_I*j);

		for(i=1;i<=nrows;i++)
			for(j=1;j<=ncols;j++)
				CU_ASSERT(Mat_get(complex_matrix,i,j)==(Real)i+(Complex)_Complex_I*j);

		Mat_free(complex_matrix);
	}

	/*Index case.*/
	{
	int i,j;
	imat* index_matrix = imat_alloc(nrows,ncols);
	for(i=1;i<=nrows;i++)
		for(j=1;j<=ncols;j++)
			Mat_set(index_matrix,i,j,(Index)i+(Index)j);

	for(i=1;i<=nrows;i++)
		for(j=1;j<=ncols;j++)
			CU_ASSERT(Mat_get(index_matrix,i,j)==(Index)i+(Index)j);


		Mat_free(index_matrix);
	}


}




int main(){
	CU_pSuite pSuite = NULL;



	/*Initialization and cleanup.*/
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();
	pSuite = CU_add_suite("Basic Matrix tests",mat_init,mat_cleanup);
	if(NULL==pSuite){
		CU_cleanup_registry();
		return CU_get_error();
	}



	/*Add tests and run.*/
	if(
			(NULL == CU_add_test(pSuite,"Testing matrix allocation",test_alloc))||
			(NULL == CU_add_test(pSuite,"Testing matrix file I/O",test_bin_IO))||
			(NULL == CU_add_test(pSuite,"Testing matrix getter/setters",test_bin_IO))
		){
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();


}
