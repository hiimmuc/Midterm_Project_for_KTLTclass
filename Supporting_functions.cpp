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