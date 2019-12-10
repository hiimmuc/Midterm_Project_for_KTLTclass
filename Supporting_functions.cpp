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
		free(*(arr + i));
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
//print_map
void print_map(int** driver, int** cus_initp, int numd, int numc) {
	char** coordinate = (char**)malloc(11 * sizeof(char*));
	for (int i = 0; i < 11; ++i) {
		coordinate[i] = (char*)malloc(11 * sizeof(char));
	}
	for (int i = 0; i < 11; ++i) coordinate[0][i] = (char)(47 + i);
	for (int j = 0; j < 11; ++j) coordinate[j][0] = (char)(47 + j);
	coordinate[0][0] = '*';
	for (int i = 1; i < 11; ++i) {
		for (int j = 1; j < 11; ++j) {
			coordinate[i][j] = '+';
		}
	}
	for (int i = 1; i < 11; ++i) {
		for (int j = 1; j < 11; ++j) {
			for (int k = 0; k < numc; ++k) {
				if (i == (cus_initp[k][0] + 1) && j == (cus_initp[k][1] + 1))
					coordinate[i][j] = 'C';
			}
			for (int k = 0; k < numd; ++k) {
				if (i == (driver[k][0] + 1) && j == (driver[k][1] + 1)) {
					if (coordinate[i][j] == 'C')  coordinate[i][j] = 'X';
					else coordinate[i][j] = 'D';
				}
			}
		}
	}
	for (int i = 10; i >= 0; --i) {
		for (int j = 0; j < 11; ++j) {
			printf_s("%4c", coordinate[i][j]);
		}
		printf_s("\n"); printf_s("\n");
	}
}