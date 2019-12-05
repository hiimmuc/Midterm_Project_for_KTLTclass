#pragma once
#pragma once
#ifndef optimize
#define optimize
#define DangPhuongNam no1

#ifdef __cplusplus
extern "C" {
#endif
	//===================main function=====================//
	int** hungarian_algo(int** input_mat, int num_of_rows, int num_of_cols);

#ifdef __cplusplus
}
#endif

#endif // !optimize.h
