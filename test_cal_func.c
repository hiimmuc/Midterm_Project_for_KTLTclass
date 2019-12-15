//#include<stdio.h>
//#include<conio.h>
//#include"supporting_functions.h"
//#include"calculation_functions.h"
//
//void main() {
//	int row = 5, col = 5;
//	int num_task = 5;
//	int** mat = allocate(row, col);
//	int** drivers = allocate(row, 2);
//	int** cus_initp = allocate(col, 2);
//	int** cus_finalp = allocate(col, 2);
//	//manually way
//	//printf_s("enter test case\n\drivers_position:\n");
//	//scan_mat(drivers, row, 2);
//	//printf_s("cus_init_position:\n");
//	//scan_mat(cus_initp, col, 2);
//	//printf_s("cus_final_position:\n");
//	//scan_mat(cus_finalp, col, 2);
//	//randomly way
//	drivers = creat_random_matrix(5, 2, 0, 9);
//	cus_initp = creat_random_matrix(5, 2, 0, 9);
//	cus_finalp = creat_random_matrix(5, 2, 0, 9);
//	mat = calculate_distances(drivers, cus_initp, cus_finalp, row, col);
//	print_mat(mat, row, col);
//	free_al(mat, row, col);
//	free_al(drivers, row, 2);
//	free_al(cus_initp, col, 2);
//	free_al(cus_finalp, col, 2);
//	_getch();
//}
