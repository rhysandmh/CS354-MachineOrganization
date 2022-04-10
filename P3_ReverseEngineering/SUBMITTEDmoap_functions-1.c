
// for each of the following functions 
// correct the prototype
// write function body
// replace return with the correct return statement
//
// you may write as many helper functions here as you wish

//Fake functions - need fixing
//Hint: -Only use integers, pointers to integers,and void functions
//		
//Algorithm 1
int algorithm_1() {
	int x = 8000;
	int y = 63;
	y = x + y;
    return y;  
}
//Algorithm 2
int algorithm_2(int x, int y) {
	int a = x;	
	int b = y; 
	if(b>=a){	
		int c = a;
		a = a + a;
		a = a + c;
		a = a + b;
		return a; 	
	}
	a = a / b;
    return a;
}
//Algorithm 3 HELPER
int alg3_helper(int input){
	input = input - 1;
	return input;
}
//Algorithm 3
int algorithm_3(int x, int y) {
	int retVal = 0;
	int zero = 0;
	int a = x;	
	int b = y;
	while(b > zero){
		retVal = retVal + a;
		b = alg3_helper(b);
	}	
	return retVal;
}
//Algorithm 4 -> Call by reference | Void
void algorithm_4(int x, int* pt) {
	x = x*3;
	*pt = x;
}



