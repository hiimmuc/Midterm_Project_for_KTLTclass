#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"Supporting_functions.h"
//allocate func
int** allocate(int number_of_row, int number_of_cols) {
	int** arr = (int**)malloc(number_of_row * sizeof(int*));
	for (int i = 0; i < number_of_row; ++i) {
		arr[i] = (int*)calloc(number_of_cols, sizeof(int));
	}
	if (arr == NULL)
	{
		printf_s("can not allocate memory...");
		exit(0);
	}
	return arr;
}
//free func
void free_al(int** arr, int number_of_rows, int number_of_cols) {
	for (int i = 0; i < number_of_rows; ++i) {
		free(arr[i]);
	}
	free(arr);
}
//print_mat
void print_mat(int** arr, int num_of_rows, int num_of_cols)
{
	printf_s("\n");
	for (int i = 0; i < num_of_rows; ++i) {
		for (int j = 0; j < num_of_cols; ++j) {
			printf("%-4d", arr[i][j]);
		}
		printf("\n");
	}
}
//scan_mat
int** scan_mat(int** arr, int num_of_rows, int num_of_cols)
{
	for (int i = 0; i < num_of_rows; i++) {
		for (int j = 0; j < num_of_cols; j++) {
			printf_s("a[%d][%d]=", i + 1, j + 1);
			scanf_s("%d%*c", &arr[i][j]);
		}
		printf_s("\n");
	}
	return arr;
}
//copy mat
void copy_mat(int** arr1, int** arr2, int numofrows, int numofcols) {
	for (int i = 0; i < numofrows; ++i) {
		for (int j = 0; j < numofcols; ++j) {
			arr1[i][j] = arr2[i][j];
		}
	}
}
//void print_map(int** driver, int** cus_initp, int numd, int numc)
//{
//	printf_s("\n/*===============MAP==============*/\n");
//	printf_s("\n");
//	for (int i = 9; i >= 0; --i) {
//		printf_s("%d", i);
//		for (int a = 0; a < numd; ++a) {
//				for (int j = 1; j <=9; ++j)
//				{
//					
//					if (j == driver[a][0] && i == driver[a][1]) {
//						printf_s("D---");
//					}
//					else
//						printf_s("|---");
//					if (j == cus_initp[a][0] && i == cus_initp[a][1]) {
//						printf_s("C---");
//					}
//					if (j == 9) {
//						printf_s("|");
//						break;
//					}
//					else
//						printf_s("|---");
//				}
//				printf_s("\n");
//			
//		}
//	}
//	for (int i = 0; i <= 9; i++) {
//		printf_s("%2d  ", i);
//	}
//
//} //logical error
