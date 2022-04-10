#include <stdio.h>

// this function prints number to the screen
// the definition is found in driver.c
int Print_One_Number(int number);

// this function returns the index of the maximum
// value in an array of integers
// arrays are 0 based
// in the event of a tie, return the first instance
int Find_Max(int n, int *a) {
    printf("The length of the array is %d\n", n);
    Print_One_Number(n);
    return -1;
}
