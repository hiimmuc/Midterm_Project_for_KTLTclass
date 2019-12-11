#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Supporting_functions.h"
#include "Optimize_algorithm.h"

//===========================MAIN PART====================================//
//find minimum element 
int find_min(int *arr, int size) {
	int min=arr[0];
	for (int i = 0; i < size; ++i) {
		min = min <= arr[i] ? min : arr[i];
	}
	return min;
}
//subtract func in step 1 and 2
int** subtract_mat_1(int** mat, int num_of_rows, int num_of_cols) {
	int min = 0;
	int i, j, k = 0;
	int** col_arr = allocate(num_of_cols, num_of_rows);
	//subtract rows
	for (i = 0; i < num_of_rows; ++i) {
		min = find_min(mat[i], num_of_cols);
		for (j = 0; j < num_of_cols; ++j) {
			mat[i][j] =mat[i][j]-min;
		}
	}
	//subtract cols
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			col_arr[j][i] = mat[i][j];
		}
	}
	for (i = 0; i < num_of_rows; ++i) {
		min = find_min(col_arr[i], num_of_cols);
		for (j = 0; j < num_of_cols; ++j) {
			mat[j][i] = mat[j][i] - min; 
		}
	}
	free_al(col_arr,num_of_cols,num_of_rows);
	return mat;
} 
//subtract func in step 4
int** subtract_mat_2(int** mat,int** masked_mat, int num_of_rows, int num_of_cols) {
	int** ans = allocate(num_of_rows, num_of_cols);
	int* temp = (int*)calloc(num_of_rows*num_of_cols, sizeof(int));
	int i, j, k=0;
	int min = 0, temp1 = 0;
//==============================================
	for (i = 0; i < num_of_rows;++i) {
		for (j = 0; j < num_of_cols; ++j) {
			//1,2
			if (masked_mat[i][j] == 0) {
				temp1=mat[i][j];
				temp[k] = temp1;
				++k;//number of non-zero element
			}
		}
	}
	min = find_min(temp, k);
	//3 subtract
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			if (masked_mat[i][j] == 0) {
				mat[i][j] -= min;
			}
			if (masked_mat[i][j] == 2) {
				mat[i][j] += min;
			}
		}
	}
	//5
	copy_mat(ans, mat,num_of_rows,num_of_cols);
	free(temp);
	return ans;
}
//draw minimun line through all zero elements in step 3
int count_crossed_line_by_col(int** mat, int num_of_rows, int num_of_cols) {
	int num = 0;
	int i, j, k = 0;
	int* col_zero, * row_zero, * crossed_row, * crossed_col;
	col_zero = (int*)calloc(num_of_cols, sizeof(int));
	row_zero = (int*)calloc(num_of_rows, sizeof(int));
	crossed_row = (int*)calloc(num_of_rows, sizeof(int));
	crossed_col = (int*)calloc(num_of_cols, sizeof(int));
	int** crossed_mat = allocate(num_of_rows, num_of_cols);
	int** process_mat = allocate(num_of_rows, num_of_cols);
	copy_mat(process_mat, mat, num_of_rows, num_of_cols);
	//count zero in col
	for (i = 0; i < num_of_cols; ++i) {
		for (j = 0; j < num_of_rows; ++j) {
			if (process_mat[j][i] == 0) {
				col_zero[i] += 1;
			}
		}
	}
	//draw line in row by assign -1 for all elements
	int temp1, temp2;
	temp1 = num_of_cols;
	temp2 = col_zero[0];
	for (i = 1; i < num_of_cols; ++i) {
		temp2 = temp2 < col_zero[i] ? temp2 : col_zero[i];
	}//find min number of col_zero
	while (temp1 > temp2) {
		for (i = 0; i < num_of_cols; ++i) {
			if (col_zero[i] == temp1) {
				for (j = 0; j < num_of_cols; ++j) {
					process_mat[j][i] = (-1);
					crossed_mat[j][i] += 1;
				}
			}
		}
		--temp1;
	}
	//count zero in row
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			if (process_mat[i][j] == 0) {
				row_zero[i] = row_zero[i] + 1;
			}
		}
	}
	//draw line in col by assign -1 for all elements
	for (i = 0; i < num_of_rows; ++i) {
		if (row_zero[i] > 0) {
			for (j = 0; j < num_of_cols; ++j) {
				process_mat[i][j] = -1;
				crossed_mat[i][j] += 1;
			}
		}
	}
	//calculate number of line
		//for row
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			if (process_mat[i][j] == -1) {
				crossed_row[i] += 1;
			}
		}
	}
	//for col
	for (i = 0; i < num_of_cols; ++i) {
		for (j = 0; j < num_of_rows; ++j) {
			if (process_mat[j][i] == -1) {
				crossed_col[i] += 1;
			}
		}
	}
	//sum up 2 type
	for (i = 0; i < num_of_rows; ++i) {
		if (crossed_row[i] == num_of_cols) {
			num += 1;
		}
	}
	if (num != num_of_cols) {
		for (i = 0; i < num_of_cols; ++i)
		{
			if (crossed_col[i] == num_of_rows) {
				num += 1;
			}
		}
	}
	copy_mat(mat, crossed_mat, num_of_rows, num_of_cols);//copy crossed mat to temp
	free_al(crossed_mat, num_of_rows, num_of_cols);
	free_al(process_mat, num_of_rows, num_of_cols);
	free(col_zero); free(row_zero); free(crossed_col); free(crossed_row);
	return num;
}
int count_crossed_line_by_row(int** mat, int num_of_rows, int num_of_cols) {
	int num = 0;
	int i, j, k = 0;
	int* col_zero, * row_zero, * crossed_row, * crossed_col;
	col_zero = (int*)calloc(num_of_cols, sizeof(int));
	row_zero = (int*)calloc(num_of_rows, sizeof(int));
	crossed_row = (int*)calloc(num_of_rows, sizeof(int));
	crossed_col = (int*)calloc(num_of_cols, sizeof(int));
	int** crossed_mat = allocate(num_of_rows, num_of_cols);
	int** process_mat = allocate(num_of_rows, num_of_cols);
	copy_mat(process_mat, mat, num_of_rows, num_of_cols);
	//count zero in row
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			if (process_mat[i][j] == 0) {
				row_zero[i] += 1;
			}
		}
	}
	//draw line in row by assign -1 for all elements
	int temp1, temp2;
	temp1 = num_of_rows;
	temp2 = row_zero[0];
	for (i = 1; i < num_of_rows; ++i) {
		temp2 = temp2 < row_zero[i] ? temp2 : row_zero[i];
	}//find min number of row_zero
	while (temp1 > temp2) {
		for (i = 0; i < num_of_rows; ++i) {
			if (row_zero[i] == temp1) {
				for (j = 0; j < num_of_cols; ++j) {
					process_mat[i][j] = (-1);
					crossed_mat[i][j] += 1;
				}
			}
		}
		--temp1;
	}
	//count zero in col
	for (i = 0; i < num_of_cols; ++i) {
		for (j = 0; j < num_of_rows; ++j) {
			if (process_mat[j][i] == 0) {
				col_zero[i] = col_zero[i] + 1;
			}
		}
	}
	//draw line in col by assign -1 for all elements
	for (i = 0; i < num_of_cols; ++i) {
		if (col_zero[i] > 0) {
			for (j = 0; j < num_of_rows; ++j) {
				process_mat[j][i] = -1;
				crossed_mat[j][i] = crossed_mat[j][i] + 1;
			}
		}
	}
	//calculate number of line
		//for row
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			if (process_mat[i][j] == -1) {
				crossed_row[i] += 1;
			}
		}
	}
	//for col
	for (i = 0; i < num_of_cols; ++i) {
		for (j = 0; j < num_of_rows; ++j) {
			if (process_mat[j][i] == -1) {
				crossed_col[i] += 1;
			}
		}
	}
	//sum up 2 type
	for (i = 0; i < num_of_rows; ++i) {
		if (crossed_row[i] == num_of_cols) {
			num += 1;
		}
	}
	if (num != num_of_cols) {
		for (i = 0; i < num_of_cols; ++i)
		{
			if (crossed_col[i] == num_of_rows) {
				num += 1;
			}
		}
	}
	copy_mat(mat, crossed_mat, num_of_rows, num_of_cols);//copy crossed mat to temp
	free_al(crossed_mat, num_of_rows, num_of_cols);
	free_al(process_mat, num_of_rows, num_of_cols);
	free(col_zero); free(row_zero); free(crossed_col); free(crossed_row);
	return num;
}
//if the number of line equal number of tasks, we assign
/*==================================================================*/
int** assign_mat(int** assignable_mat, int num_of_rows, int num_of_cols) {
	/*make the assign point become -8(for team8) :D*/
	int** ans = allocate(num_of_rows, num_of_cols);
	int** temp1 = allocate(num_of_rows, num_of_cols);
	int** temp2 = allocate(num_of_rows, num_of_cols);
	int i, j, k, pos = 0;
	int count_1 = 0, count_2 = 0, min_row = 0, min_col = 0;
	int num_of_task = num_of_cols;
	int* count_row, *count_col;
	count_row = (int*)calloc(num_of_rows, sizeof(int));
	count_col = (int*)calloc(num_of_cols, sizeof(int));
	copy_mat(temp1, assignable_mat, num_of_rows, num_of_cols);
	copy_mat(temp2, assignable_mat, num_of_rows, num_of_cols);
	//count zero in each row and col
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			if (temp1[i][j] == 0 && temp2[i][j] == 0) {
				count_row[i] += 1;
				count_col[j] += 1;
			}
		}
	}
	min_row = find_min(count_row, num_of_cols);
	min_col = find_min(count_col, num_of_rows);
	for (int y = 1; y <= num_of_task; ++y) {
		for (i = 0; i < num_of_rows; ++i) {
			if (count_row[i] == min_row) {
				for (j = pos; j < num_of_cols; ++j) {
					if (temp1[i][j] == 0) {
						++count_1;
						//draw -1 line through all num of elements in 2 line intersect in temp1[i][j]
						for (k = 0; k < num_of_task; ++k) {
							temp1[i][k] = -1;
							temp1[k][j] = -1;
						}
						temp1[i][j] = -8;//assign the choosen zero by -8
						//reset the count_row array to zero to count again(after assign)
						for (int a = 0; a < num_of_rows; ++a) {
							count_row[a] = 0;
						}
						//count again
						for (int a = 0; a < num_of_rows; ++a) {
							for (int b = 0; b < num_of_cols; ++b) {
								if (temp1[a][b] == 0) {
									count_row[a] += 1;
								}
							}
						}
					}
				}
				//set the covered row'value equal numofrow+1 in oder to make the other row can be the minimum
				for (int a = 0; a < num_of_rows; ++a) {
					if (count_row[a] == 0) {
						count_row[i] = num_of_rows + 1;
					}
				}
				//find min again
				min_row = find_min(count_row, num_of_rows);
			}
		}
	}
	for (int x = 1; x <= num_of_task; ++x) {
		for (i = 0; i < num_of_cols; ++i) {
			if (count_col[i] == min_col) {
				for (j = 0; j < num_of_rows; ++j) {
					if (temp2[j][i] == 0) {
						++count_2;
						//draw -1 line through all num of elements in 2 line intersect in temp2[i][j]
						for (k = 0; k < num_of_task; ++k) {
							temp2[j][k] = -1;
							temp2[k][i] = -1;
						}
						temp2[j][i] = -8;//assign the choosen zero by -8
						//reset the count_col array to zero to count again(after assign)
						for (int a = 0; a < num_of_cols; ++a) {
							count_col[a] = 0;
						}
						//count again
						for (int a = 0; a < num_of_cols; ++a) {
							for (int b = 0; b < num_of_rows; ++b) {
								if (temp2[b][a] == 0) {
									count_col[a] += 1;
								}
							}
						}
					}
				}
				//set the covered col's value equal numofcol+1 in oder to make the other col can be the minimum
				for (int a = 0; a < num_of_cols; ++a) {
					if (count_col[a] == 0) {
						count_col[i] = num_of_cols + 1;
					}
				}
				//find min again
				min_col = find_min(count_col, num_of_rows);
			}
		}
	}
	if (count_1 == num_of_task) {
		copy_mat(ans, temp1, num_of_rows, num_of_cols);
	}
	else if (count_2 == num_of_task) {
		copy_mat(ans, temp2, num_of_rows, num_of_cols);
	}
	free(count_row); free(count_col); free_al(temp1, num_of_rows, num_of_cols); free_al(temp2, num_of_rows, num_of_cols);
	return ans;
}
/*==================================================================*/
int** make_square(int** mat, int row, int col) {
	//num of cus less than num of drivers
	if (row > col) {
		for (int i = 0; i < row; ++i) {
			mat[i] = (int*)realloc(mat[i], row * sizeof(int));
		}
		for (int i = 0; i < row; ++i) {
			for (int j = col; j < row; ++j) {
				mat[i][j] = 0;
			}
		}
	}
	//num of driver less than num of cus
	if (col > row) {
		mat = (int**)realloc(mat, sizeof(int*) * col);
		for (int i = row; i < col; ++i) {
			mat[i] = (int*)calloc(col , sizeof(int));
		}
	}
	return mat;
}
/*==================================================================*/
int** hungarian_algo(int** input_mat, int num_of_rows, int num_of_cols)
{//===> prepare part
	int i, j, k = 0;
	int temp1 = num_of_rows, temp2 = num_of_cols, tmp1, tmp2;
	int number_of_crossed_lines=0;
	int num_task = num_of_rows <= num_of_cols ? num_of_cols : num_of_rows;//num of task equal the bigger one
	int** temp_mat1, ** temp_mat2, ** temp_mat;
	int	**pre_ans, ** final_result;
	int** process_mat = allocate(num_of_rows, num_of_cols);
	//copy to process mat
	copy_mat(process_mat, input_mat, num_of_rows, num_of_cols);
	//check whether the input_mat is square or not, if not make it squared
	if (num_of_rows != num_of_cols) {
		input_mat = make_square(input_mat, num_of_rows, num_of_cols);
		process_mat = make_square(process_mat, num_of_rows, num_of_cols);
		num_of_cols = num_task;
		num_of_rows = num_task;
	}//the num_of_rows now is same as num_of_cols
	temp_mat1 = allocate(num_of_rows, num_of_cols); 
	temp_mat2 = allocate(num_of_rows, num_of_cols); 
	temp_mat = allocate(num_of_rows, num_of_cols);
	pre_ans = allocate(num_of_rows, num_of_cols);
	final_result = allocate(num_task, 3);
//======>step1
	pre_ans = subtract_mat_1(process_mat, num_of_rows,num_of_cols);
	 do {
		copy_mat(temp_mat1, process_mat, num_of_rows, num_of_cols);
		tmp1 = count_crossed_line_by_row(temp_mat1, num_of_rows, num_of_cols);
		copy_mat(temp_mat2, process_mat, num_of_rows, num_of_cols);
		tmp2= count_crossed_line_by_col(temp_mat2, num_of_rows, num_of_cols);
		if (tmp1 <= tmp2) {
			number_of_crossed_lines = tmp1;
			copy_mat(temp_mat, temp_mat1, num_of_rows, num_of_cols);
		}
		else{
			number_of_crossed_lines = tmp2;
			copy_mat(temp_mat, temp_mat2, num_of_rows, num_of_cols);
		}//to choose the minimum number of crossed line
		//if the crossed line is not equal num of task, we subtract 2nd time
		if (number_of_crossed_lines != num_task) {
			process_mat = subtract_mat_2(process_mat, temp_mat, num_of_rows, num_of_cols); 

		}
	} while (number_of_crossed_lines != (num_task));
		copy_mat(pre_ans, process_mat, num_of_rows, num_of_cols);
	if (number_of_crossed_lines == num_task) {
		//we can assign
		pre_ans = assign_mat(process_mat, num_of_rows, num_of_cols);
		//printf_s("\nAssigned_mat:\n");print_mat(pre_ans, num_of_rows, num_of_cols); //enable when testing
		//convert to output mat(n x 3)
		for (i = 0; i < num_of_rows; ++i) {
			for (j = 0; j < num_of_cols; ++j) {
				if (pre_ans[i][j] == -8) {
					final_result[k][0] = j;
					final_result[k][1] = i;
					final_result[k][2] = input_mat[i][j];
					++k;
				}
			}
		}
	}
	free_al(temp_mat, num_of_rows, num_of_cols); free_al(temp_mat1, num_of_rows, num_of_cols); free_al(temp_mat2, num_of_rows, num_of_cols);
	free_al(process_mat, num_of_rows, num_of_cols);
	free_al(pre_ans, num_of_rows, num_of_cols);
	num_of_rows = temp1;
	num_of_cols = temp2;
	return final_result;
}
