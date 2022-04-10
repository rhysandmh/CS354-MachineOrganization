// Do all of your work in assembly in the the .s files 

#include <stdio.h>
#define ARRAY_LENGTH 5

int Find_Max(int n, int *a);
void Print_One_Number(int number) {
    printf("The number is %d\n",number);
    return;
}

int main() {
    int A[ARRAY_LENGTH] = {86, 95, 52, 95, 101};

    // Arrays are 0 based.
    // In the event of ties report the first instance
    // The index of the maximum value in the above array is 4.

    int index = Find_Max(ARRAY_LENGTH, A);
    printf("The maximum value in the array is found at index %d\n", index);

    return 0;
}
