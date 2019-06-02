#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

typedef int (*sort_compare_t)(void *arg1, void *arg2);

typedef void (*sort_swap_t)(void *arg1, void *arg2);

void sort_run(int*data, int n, sort_compare_t fwxCompare, sort_swap_t fxcSwap);




#endif // SORT_H_INCLUDED
