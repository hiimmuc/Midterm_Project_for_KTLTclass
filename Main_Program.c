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

////should test for nxn case

void main(int argc, char* argv[]) {
	printf_s("/*==========HELLO=========*/\n");
	//kind of maps
	int num_of_cus = count("customer_data.txt");//count customers
	int num_of_drv = count("driver_data.txt");//count drivers

	customer* c = (customer*)calloc(num_of_cus, sizeof(customer));
	// allocate memory for number of customers counted above
	driver* d = (driver*)calloc(num_of_drv, sizeof(driver));
	//same as above
	constructC(num_of_cus, c);
	constructD(num_of_drv, d);
	int** cusCipMat = allocate(num_of_cus, 2);//allocate memory for cip mattrix
	getCusCip(cusCipMat, c, num_of_cus);//get values for cip mattrix

	int** CusCfpMat = allocate(num_of_cus, 2);//same
	getCusCfp(CusCfpMat, c, num_of_cus);//same

	int** DrvDpMat = allocate(num_of_drv, 2);//same
	getDrvDp(DrvDpMat, d, num_of_drv);//same
	int col, row;
	col = num_of_drv;
	row = num_of_cus;
	int num_task = row <= col ? row : col;
	//creat matrix of data
	int** mat = allocate(row, col);
	int** result = allocate(row, 3);
	int** result_2 = allocate(num_task, 5);
	int** drivers = allocate(row, 2);
	int** cus_initp = allocate(col, 2);
	int** cus_finalp = allocate(col, 2);
	//system("cls");
	//printf map
	//print_map(drivers, cus_initp, row, col);
	copy_mat(drivers, DrvDpMat, num_of_drv, 2);
	copy_mat(cus_initp, cusCipMat, num_of_cus, 2);
	copy_mat(cus_finalp, CusCfpMat, num_of_cus, 2);
	//pr0cess
	mat = calculate_distances(drivers, cus_initp, cus_finalp, col, row);
	//process
	result = hungarian_algo(mat, row, col);
    //
	result_2 = calculate_time_and_fee(result, drivers, cus_initp, cus_finalp, row, col);
	printf_s("\n\nresult(output_matrix2)):\n\
1st col for number of customer\n\
2nd col for number of drivers\n\
3rd col for estiamted time taken\n\
4th col for estimated time arriving final point\n\
5th col for the total money");
	print_mat(result_2, num_task, 5);
	//end game
	free_al(result_2, num_task, 5);
	free_al(cus_finalp, col, 2); free_al(drivers, row, 2); free_al(cus_initp, col, 2);
	free_al(mat, row, col);
	free_al(result, row, 3);
	_getch();
}