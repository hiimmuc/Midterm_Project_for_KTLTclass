#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include "Supporting_functions.h"
#include "IO_files.h"
#include "Calculation_functions.h"
#include "Optimize_algorithm.h"

void main(int argc, char* argv[]) {
	printf_s("/*==========HELLO=========*/\n");
	//input part
	int num_of_cus = count("customer_data.txt");//count customers
	int num_of_drv = count("driver_data.txt");//count drivers
	//allocate memory for cus and drvs
	customer* c = (customer*)calloc(num_of_cus, sizeof(customer));
	driver* d = (driver*)calloc(num_of_drv, sizeof(driver));
	//
	constructC(num_of_cus, c);
	constructD(num_of_drv, d);
	int** cusCipMat = allocate(num_of_cus, 2);//allocate memory for cip mattrix
	getCusCip(cusCipMat, c, num_of_cus);//get values for cip mattrix

	int** CusCfpMat = allocate(num_of_cus, 2);//same
	getCusCfp(CusCfpMat, c, num_of_cus);//same

	int** DrvDpMat = allocate(num_of_drv, 2);//same
	getDrvDp(DrvDpMat, d, num_of_drv);//same
	int col, row;
	row = num_of_drv;
	col = num_of_cus;
	int num_task = row <= col ? row : col;
	//creat matrix of data
	int** mat = allocate(row, col);
	int** result = allocate(row, 3);
	int** result_2 = allocate(num_task, 5);
	int** drivers = allocate(row, 2);
	int** cus_initp = allocate(col, 2);
	int** cus_finalp = allocate(col, 2);
	system("cls");
	copy_mat(drivers, DrvDpMat, num_of_drv, 2);
	copy_mat(cus_initp, cusCipMat, num_of_cus, 2);
	copy_mat(cus_finalp, CusCfpMat, num_of_cus, 2);
	printf_s("\n\t/*============ M A P ============*/\n\n");
	print_map(drivers, cus_initp, row, col);
	//pr0cess
	mat = calculate_distances(drivers, cus_initp, cus_finalp, row, col);
	//process
	result = hungarian_algo(mat, row, col);
	result_2 = calculate_time_and_fee(result, drivers, cus_initp, cus_finalp, row, col, 1);
	printf_s("\n\nresult(output_matrix2)):\n\
1st col for number of customer\n\
2nd col for number of drivers\n\
3rd col for estimated time taken\n\
4th col for estimated time arriving final point\n\
5th col for the total money");
	print_mat(result_2, num_task, 5);
	billForCus* Bills = (billForCus*)malloc(num_of_cus * sizeof(billForCus));
	constructBill(num_of_cus, Bills, result_2, c, d);
	printBill(num_of_cus, Bills);
	printf_s("\nDone!!!");
	//free memories
	free(c); free(d); free_al(cusCipMat,num_of_cus,2); free_al(CusCfpMat, num_of_cus, 2); free_al(DrvDpMat, num_of_drv, 2);
	free_al(result_2, num_task, 5);
	free_al(cus_finalp, col, 2); free_al(drivers, row, 2); free_al(cus_initp, col, 2);
	free_al(mat, row, col);
	free_al(result, row, 3);
	_getch();
}