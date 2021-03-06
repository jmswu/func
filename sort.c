#include "sort.h"


/*
 * bubble sort
 */
void sort_run(int *data, int n, sort_compare_t fxcCompare, sort_swap_t fxcSwap){
    int isSwaped; // indicate data is swapped
    int pass = 0;

    do {
        isSwaped = 0; // reset flag

        // loop through all data
        for(int i = 0; i < n - pass - 1; i++){

            if (fxcCompare(&data[i], &data[i + 1])){ // compare data
                fxcSwap(&data[i], &data[i + 1]); // swap data
                isSwaped = 1; //indicate data is swapped
            }
        }
        
        pass++;

    }while(isSwaped == 1); // repeat if data is swapped
}

