#pragma once
#pragma once
#ifndef Supporting_functions
#define Supporting_functions

#ifdef __cplusplus
extern "C" {
#endif
	//===============supporting functions===================//
	int** allocate(int number_of_row, int number_of_cols);
	void free_al(int** arr, int number_of_rows, int number_of_cols);
	void print_mat(int** arr, int num_of_rows, int num_of_cols);
	int** scan_mat(int** arr, int num_of_rows, int num_of_cols);
	void copy_mat(int** mat1, int** mat2, int row, int col);
	void print_map(int** driver, int** cus_initp, int numd, int numc);
#ifdef __cplusplus
}
#endif

#endif // !optimize.h
