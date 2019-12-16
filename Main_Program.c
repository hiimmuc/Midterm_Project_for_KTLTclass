#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "Supporting_functions.h"
#include "IO_files.h"
#include "Calculation_functions.h"
#include "Optimize_algorithm.h"

#define max 100

int main(int argc, char* argv[]) {
	printf_s("/*==========HELLO=========*/\n");
	//input part
	int ans_;
	do {
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
		printf_s("\n /*============ Map of positions ============*/\n\n");
		print_map(drivers, cus_initp, row, col);
		//pr0cess
		//calulate distances
		mat = calculate_distances(drivers, cus_initp, cus_finalp, row, col);
		//print_mat(mat, row, col);
		//optimize
		result = hungarian_algo(mat, row, col);
		//print_mat(result, row, col);
		//calculate time and cash
		result_2 = calculate_time_and_cash(result, drivers, cus_initp, cus_finalp, row, col);
		//print_mat(result_2, row, col);
		//print bill
		billForCus* Bills = (billForCus*)malloc(num_of_cus * sizeof(billForCus));
		constructBill(num_of_cus, Bills, result_2, c, d);
		printBill(num_of_cus, Bills);
		//print commands
		char ans;
		printf_s("\nPress any keys to continue.....");
		_getch();
		//
		for (int i = 0; i < num_task; ++i) {
			system("cls");
			printf_s("\n/>Driver [%d] in ( %d, %d) please move to ( %d, %d) to take customer [%d]\n\
 >Mr(Mrs): %s\n\n\
 >Estimated time: %d minutes\n\
 >Take customer to ( %d, %d) in %d minutes\n\
 >Customer phone: %s\n\
 >>Total cash: %d,000 VND\n>>THANK YOU<<\n\
***\n", result_2[i][1] + 1, drivers[i][0], drivers[i][1], cus_initp[result_2[i][0]][0], cus_initp[result_2[i][0]][1], result_2[i][0] + 1, c[result_2[i][0]].name, result_2[i][2], cus_finalp[result_2[i][0]][0], cus_finalp[result_2[i][0]][1], result_2[i][3], c[result_2[i][0]].phone, result_2[i][4]);
			printf_s("/>Driver [%d] confirm(y/n):  ", result_2[i][1] + 1); scanf_s("%c%*c", &ans); fflush(stdin);
			/*while (getchar() != '\n'); ans = getchar();*/
			if (ans == 'y' || ans == 'Y') {
				printf_s("\n/>Driver [%d] status: CONFIRMED\n", result_2[i][1] + 1);
				printf_s("\nPress any keys to continue.....");
				_getch();
			}
			else if (ans == 'n' || ans == 'N') {
				printf_s("\n/>Driver [%d] status: not confirmed\n", result_2[i][1] + 1);
				printf_s("\nPress any keys to continue.....");
				_getch();
			}
		}
		system("cls");
		printf_s("\nCommand List:\n");
		for (int i = 0; i < num_task; ++i) {
			printf_s("\n/>Driver[%d] will take customer [%d]", result[i][1] + 1, result[i][0] + 1);
		}
    
		printf_s("\n\n\t Have a nice trip\n\t ++++GOOD BYE++++\n\n\tVUI VE? KHONG QUAU. :D \n\
/*===========================================================*/");

		/*====================================================================================================================*/
		//update driver posotions

		updateDrvData(num_of_drv, c, d, result_2);

		//repeat
		printf_s("\n\nContinue?:\n1.Yes\n2.No\nYour choice:  ");
		scanf_s("%d%*c", &ans_); fflush(stdin);
		//system("cls");
		time_t tm;
		srand((int)time(&tm));
		if (ans_ == 1) {
			for (int t = 0; t < num_of_cus; ++t) {
				printf_s("\nEnter customer[%d] name: ", t + 1); fgets(c[t].name, max, stdin); fflush(stdin);
				printf_s("Enter customer[%d] phone:", t + 1); fgets(c[t].phone, max, stdin); fflush(stdin);
				//for shrotening the time we use random number :D
				c[t].cip[0] = (0 + rand() % (9 + 1 - 0));
				c[t].cip[1] = (0 + rand() % (9 + 1 - 0));
				c[t].cfp[0] = (0 + rand() % (9 + 1 - 0));
				c[t].cfp[1] = (0 + rand() % (9 + 1 - 0));
			}
			updateCusData(num_of_cus, c);
		}
		/*====================================================================================================================*/
		//free memories
		free(c); free(d); free_al(cusCipMat, num_of_cus, 2); free_al(CusCfpMat, num_of_cus, 2); free_al(DrvDpMat, num_of_drv, 2);
		free_al(result_2, num_task, 5);
		free_al(cus_finalp, col, 2); free_al(drivers, row, 2); free_al(cus_initp, col, 2);
		free_al(mat, row, col);
		free_al(result, row, 3);
		//
	} while (ans_ == 1);
	//end
	return 0;
}