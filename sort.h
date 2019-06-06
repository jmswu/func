#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

/*
 * function call back for user compare implementation for all data types
 */
typedef int (*sort_compare_t)(void *arg1, void *arg2);

/*
 * function call back for user swap implementation for all data type
 */
typedef void (*sort_swap_t)(void *arg1, void *arg2);


/** \brief sort different data as user implementation
 *
 * \param int *data, pointer to data to be short, can be change to different data type
 * \param int n, number of data
 * \param sort_compare_t fxcCompare, user compare implementation
 * \param sort_swap_t fxcSwap, user swap implementation
 * \return void
 *
 */
void sort_run(int *data, int n, sort_compare_t fxcCompare, sort_swap_t fxcSwap);

#endif // SORT_H_INCLUDED
