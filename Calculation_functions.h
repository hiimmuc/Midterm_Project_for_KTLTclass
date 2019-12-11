#pragma once
#ifndef calculation_func
#define calculation_func
#ifdef __cplusplus
extern "C" {
#endif
	int** calculate_distances(int** drivers, int** customers_initp, int** customers_finalp, int num_of_customers, int  num_of_drivers);
	int** calculate_time_and_cash(int** input_mat, int** drivers, int** customers_initp, int** customers_finalp, int num_of_customers, int  num_of_drivers);
#ifdef __cplusplus
}
#endif 

#endif // !calculation
