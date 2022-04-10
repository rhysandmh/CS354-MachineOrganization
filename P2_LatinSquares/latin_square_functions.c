/******************************************************************************
 * @file: latin_square_functions.c
 *
 * WISC NETID pbryant2
 * CANVAS USERNAME Peter Bryant
 * WISC ID NUMBER 9082596439 
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL) -Below-
 * 
 * For my implementation of Read_Latin_Square_File() I open and close the file twice, 
 * where the first time I do so I compute (n) and the second time I fill in the 2D Array. 
 * This was a suggestion from Mike I was given before lecture!
 *
 * @creator: Peter Bryannt (pbryant2@wisc.edu)
 * @modified: 11/13/2021
 *****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "latin_square_functions.h"

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }
#define dbgprint_latin_square(n, LS) if (DEBUG) { Print_Latin_Square(n, LS); }

/******************************************************************************
 * Data Types and Structures
 *****************************************************************************/

// ADD ANY ADDITIONAL DATA TYPES OR STRUCTSvHERE 

/******************************************************************************
 * Globals
 *****************************************************************************/
extern void Print_Latin_Square(const size_t n, char **latin_square);

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 

/******************************************************************************
 * Verificaiton functions
 *****************************************************************************/

/* 
 * This function takes the name of the file containing the latin square
 * and reads in the data to the the latin_square parameter.  
 *
 * There are many approaches that will work to read in the latin square data.
 * In any approach you choose, you will need to do at least the following:
 *     1) open the file 
 *     2) read in the text from the file
 *     3) figure out the dimensions of the latin square (n)
 *     4) reserve memory for the latin_square. This requires 2 steps
 *         4a) reserve an array of pointers to the rows
 *         4b) reserve an array of characters for each row
 *     5) fill in the latin_square data structure 
 *     6) close the file
 *
 * @param filename The name of the file to read in
 * @param latin_square_in A pointer to the latin square variable in main
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 */
void Read_Latin_Square_File(const char *filename, 
                            char ***latin_square_in, 
                            size_t *n) {
     /* BEGIN MODIFYING CODE HERE */
	//3) figure out the dimensions of the latin square (n) 
	FILE *filept;
	char c;
	filept = fopen(filename, "r");
	*n = 0;
	*latin_square_in = NULL;
	//Computes n
	while((c = fgetc(filept))){
		if(c == '\n'){break;}
		if(feof(filept)){break;}
		(*n)++;
	}
	fclose(filept);

	//1)Open the file 	
	FILE *fp;
	//2. Read the contents, store the file pointer
	fp = fopen(filename, "r");
	//If the file pointer is null we set the size to zero, the array to null, 
	//print an error and exit the program
	if(fp == NULL){
		*n = 0;
    	*latin_square_in = NULL;		
		printf("Error,  File Pointer Null");
		exit(1);
	}	
 	//4) reserve memory for the latin_square. This requires 2 steps
 	//4a) reserve an array of (char) pointers to the rows
	*latin_square_in = malloc((*n) * sizeof(char*));
 	//4b) reserve an array of characters for each row
	for(int i = 0; i < *n; i++){
		//(*latin_square_in) gets the first element of the array, add i to go down the rows
		*((*latin_square_in)+i) = malloc((*n) * sizeof(char));
	}
 	//5) fill in the latin_square data structure
	// 
	//Iterate through the rows and columns of the latin square
	char newChar;
	for(int i = 0; i < *n ; i++){
		for(int j = 0; j < *n ; j++){
		//Set the ith jth element to the next Char in the file
			newChar = fgetc(fp);
			//if the newChar is the new line character, skip over it
			if(newChar == '\n'){newChar=fgetc(fp);}
			*(*(*(latin_square_in)+i)+j) = newChar;	
			//printf("latin_square_in[%d][%d] = %c\n", i, j,*(*(*(latin_square_in)+i)+j) );
			//if the file pointer reaches the end of the file, end execution
			if(feof(fp)){break;}
		}
	}
 	//6) close the file
	fclose(fp);
	return;
    /* END MODIFYING CODE HERE */
}
/* 
 * This function checks to see that exactly n symbols are used and that 
 * each symbol is used exactly n times.
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
int Verify_Alphabet(const size_t n, char **latin_square) {
    if (latin_square == NULL) {
        printf("Verify_Alphabet - latin_square is NULL\n"); 
        return 0;
    }

    /* BEGIN MODIFYING CODE HERE */
	//Variable represents the possible ascii symbol values allowed per the specification
	int validSymbols = 126 - 33 + 1; // (~) - (!) + (inclusive) 
	int *symbolArray;	
	symbolArray = malloc(validSymbols * sizeof(int));
	//Clear out the new symbolArray - set all values to 0
	for(int i = 0; i < validSymbols ; i++){
		*(symbolArray+i)= 0;
	}
	//The Symbol Array will correspond to occurences of all possible Symbols, starting with "!" at index 0.
	//Everytime that a valid symbol appears in latin_square, it increments the value corresponding
	//to that symbol's index in the symbolArray.
	for(int i = 0; i < n ; i++){
		for(int j =0; j < n ; j++){
			//If the symbol is not valid - just return 0
			if((*(*(latin_square+i)+j) <  33) && (*(*(latin_square+i)+j) > 126)){
				return 0;
			}
			//Executes if the symbol found in the table was a valid character
			//The index is computed so the first valid character ('!' with ascii = 33) is at the first index (index = 0) of the symbolArray 
			int index = *(*(latin_square+i)+j) - 33;
			//This increments the count of the symbol at its new specified index (which gives us the number of occurences)
			*(symbolArray+index)= *(symbolArray+index)+1;
		}
	}
	//The following loop will go through the entire symbolArray and increment the value of uniqueSymbols everytime an element is found with 0< occurences,
	//After the loop the value of uniqueSymbols should be (n), representing every element with 0< occurences.
	int uniqueSymbols = 0;
	for(int i = 0 ; i < validSymbols ; i++){
		//This checks if the symbol has had an occurence in the symbolArray
		if(*(symbolArray+i)!= 0){
			//Eval 1: Checks that every element that occurs, occurs exactly 'n' times 			
			if(*(symbolArray+i)!= n){
				return 0;
			}
			uniqueSymbols += 1;
		}
	}
	//Eval 2: Ensures that their are "n" unique symbols in the array
	if(uniqueSymbols != n){
		printf("ERROR uniqueSymbols = %d | n = %d", uniqueSymbols, n);
		return 0;
	}
	//symbolArray was allocated with malloc and must be freed by the function
	free(symbolArray);
    /* END MODIFYING CODE HERE */
    return 1;
}

/* 
 * This function verifies that no symbol is used twice in a row or column.
 * It prints an error message alerting the user which rows or columns have 
 * duplicate symbols. This means that you will have at most n row error prints
 * and n column error prints.
 * 
 * Note: Test all rows first then test all columns.
 * 
 * Error messages have been included for you. Do not change the format out the 
 * print statements, as our grading scripts will use exact string matching. You
 * change the variable passed as the formatting argument to printf.
 * 
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
 int Verify_Rows_and_Columns(const size_t n, char **latin_square){
    if (latin_square == NULL) {
        printf("Verify_Rows_and_Columns - latin_square is NULL\n"); 
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */
	int errorOccured = 0;
	//Same as above method, need to count character frequency for each row
	int validSymbols = 126 - 33 + 1; // (~) - (!) + (inclusive) 
	int *symbolArray;	
	symbolArray = malloc(validSymbols * sizeof(int));
	
	//The Symbol Array will correspond to occurences of all possible Symbols, starting with "!" at index 0.
	//Everytime that a valid symbol appears in latin_square, it increments the value corresponding
	//to that symbol's index in the symbolArray.
	
	//Eval 1:  Use frequency counter to check the Rows for duplicates
	for(int i = 0; i < n ; i++){
		//Clear out the new symbolArray - set all values to 0
		for(int k = 0; k < validSymbols ; k++){
			*(symbolArray+k)= 0;
		}
		for(int j =0; j < n ; j++){
			//If the symbol is not valid - just return 0
			if((*(*(latin_square+i)+j) <  33) && (*(*(latin_square+i)+j) > 126)){
				return 0;
			}
			//Executes if the symbol found in the table was a valid character
			//The index is computed so the first valid character ('!' with ascii = 33) is at the first index (index = 0) of the symbolArray 
			int index = *(*(latin_square+i)+j) - 33;
			//This increments the count of the symbol at its new specified index (which gives us the number of occurences)
			*(symbolArray+index) += 1;
			//printf("%c = %d\n",*(*(latin_square+i)+j), *(symbolArray+index));
			//If their exists a duplicate entry
			if(*(symbolArray+index) > 1){
				printf("Error in row %d\n", i);
				errorOccured = 1;
			}
		}
	}
	//Eval 2: Use frequency counter to check the Columns for duplicates
	for(int i = 0; i < n ; i++){
		//Clear out the new symbolArray - set all values to 0
		for(int k = 0; k < validSymbols ; k++){
			*(symbolArray+k)= 0;
		}
		for(int j =0; j < n ; j++){
			//If the symbol is not valid - just return 0
			if((*(*(latin_square+j)+i) <  33) && (*(*(latin_square+j)+i) > 126)){
				return 0;
			}
			//Executes if the symbol found in the table was a valid character
			//The index is computed so the first valid character ('!' with ascii = 33) is at the first index (index = 0) of the symbolArray 
			int index = *(*(latin_square+j)+i) - 33;
			//This increments the count of the symbol at its new specified index (which gives us the number of occurences)
			*(symbolArray+index) += 1;
			//printf("%c = %d\n",*(*(latin_square+i)+j), *(symbolArray+index));
			//If their exists a duplicate entry
			if(*(symbolArray+index) > 1){
				printf("Error in column %d\n", i);
				errorOccured = 1;
			}
		}
	}
	free(symbolArray);
    if(errorOccured == 1){
		return 0;
	}
    /* END MODIFYING CODE HERE */
    return 1;
}
/* 
 * This function calls free to allow all memory used by the latin_square 
 * verification program to be reclaimed.
 *
 * Note: you will have n+1 calls to free
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 */ 
void Free_Memory(const size_t n, char **latin_square) {
    /* BEGIN MODIFYING CODE HERE */
  	//Free all rows in the Latin Square
	for (int i = 0; i < n; i++) {
    	free(*(latin_square + i));
  	}
	//Free the pointer to the array
  	free(latin_square);
  	return;
	/* END MODIFYING CODE HERE */
}


