/******************************************************************************
 * @file: functions.c
 *
 * WISC NETID pbryant2
 * CANVAS USERNAME Peter Bryant
 * WISC ID NUMBER 9082596439
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Peter Bryant pbryant2@wisc.edu
 * @modified: 10/7/21
 *****************************************************************************/
#include <stdio.h>
#include "functions.h"

// Some macros that may be useful to you 
#define MAX_USERNAME_LEN    32
#define MAX_EMAIL_LEN       32
#define MAX_DOMAIN_LEN      64
#define MIN_PASSWORD_LEN    8
#define MAX_PASSWORD_LEN    16
#define NEW_LINE_CHAR       10

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 
// Examples: IsLetter, IsDigit, Length, Find...

//Helper function determines if char is a digit (0-9)
//
//@param character being evaluated
//@return 1, iff it is a digit
int IsDigit(char ch){
   if(ch >= '0' && ch<= '9')
    {
        return 1; 
    }
   else
    {
        return 0;
    }
}

//Helper function determines if char is a upper or lower case letter
//
//@param character being evaluated
//@return 1, iff it is a upper or lower case letter
int IsAlpha(char ch){
    if((ch >= 'A' && ch <= 'Z') || (ch >='a' && ch <= 'z'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Helper function to compute the length of a character array.
//
//@param char pointer to array
//@param the size of the array input buffer
//@return length of char array of type int
int Length(char *s, size_t size){
    int n;
    for(n = 0; (*s != '\0'); s++){
         n++;
    }
    //Don't go past the input buffer in the array.
    if (n >= size){
        return size;
    }
        return n;
}

//Determines if two char arrays have equal contents
//
//@param array1 pointer to be compared
//@param array2 pointer to be compared with
//@param the size of array1
//@return 1, iff these arrays are equal
int Equals(char *s, char *t, int size){
    int isEqual = 1;
    for(int i = 0; i < size; i++){
        if(*(s+i) != *(t+i))
        {
            isEqual = 0;
        }
    }
    return isEqual; 
}

//Helper method to print the contents of an array.
//
//@param the array to be printed
void printArray(char *s){
    int n;
    for(n = 0 ; (*s != '\0'); s++) {
        printf("arr[%d] = %c\n", n, *s);
        n++;
    }
}

//Finds the index of a char in a char array.
//
//@param ch, char you are looking for
//@param *s, array you are searching through
//@size of the input buffer for the char array
//@returns the index of the element in the array if found, -1 if char isn't found
int Find(char ch, char *s, size_t size){
    for(int i =0 ;i < Length(s, size) ; i++){
        if(*(s+i) == ch){
            return i;
        }
    }
    return -1;
}
/******************************************************************************
 * Verification functions
 *****************************************************************************/

/*
 * A username must begin with a letter [A-Z, a-z], contain 32 characters
 * or less, and  may only consist of letters, underscores, or 
 * digits [A-Z, a-z, _, 0-9]. An error message is displayed if any of 
 * these conditions are not met. Only print the first applicable error 
 * message. 
 *
 * @param user : The username string
 * @param len : Size of the username input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Username(char user[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    dbgprintf("This line only prints if DEBUG is set to 1\n");
    //Allocate and init pointer to first element in user array
    char *pt;
    pt = user;
    //Compute Length of user array
    int strLength = Length(user, len);
    //Error 1: Username must begin with a letter
    //
    if(IsAlpha(*user) != 1)
    {
         printf(ERROR_01_USER_START_INVALID);
         return 0;
    } 
    //Error 2: Username must contain 32 characters or less
    //
    if(strLength > MAX_USERNAME_LEN)
    {
        printf(ERROR_02_USER_LEN_INVALID);
        return 0;
    }
    //Error 3: Only letters underscores or digits
    //
    for(; (*pt != '\0') && (*pt != '\n') ; pt++){
        if((IsDigit(*pt) != 1) && (IsAlpha(*pt) != 1) && (*pt) != '_')
        {
            printf(ERROR_03_USER_CHARS_INVALID);
             return 0;
        }
    }
   
    /* END MODIFYING CODE HERE */
    printf(SUCCESS_1_USER);
    return 1;
}

/*
 * An email address has four parts:
 *      name
 *          exists
 *          must start with letter
 *          max 32 characters
 *          may contain only letters and digits
 *      @ symbol
 *          exists
 *      domain name
 *          exists
 *          max of 64 characters
 *          composed of one or more subdomains separated by .
 *          subdomain must begin with a letter
 *          subdomains may contain only letters and digits
 *      top-level domain 
 *          must be [.edu, .com, .net]
 *
 * If the email address contains one or more errors print only the first
 * applicable error from the list.
 *
 * Note this task is based on a real world problem and may not be the best 
 * order to approach writing the code.
 *
 * @param email : The email string
 * @param len : Size of the email input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Email(char email[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    int at_index = 0, nameLen = 0;
    int strLength = Length(email, len);
    char *at_pt, *end_pt;
    char edu[] = {'.', 'e', 'd', 'u'};
    char com[] = {'.', 'c', 'o', 'm'};
    char net[] = {'.', 'n', 'e', 't'};

    at_index = Find('@', email, len);   //Computes the index of the "@" symbol
    at_pt = &email[at_index];           //Creates a pointer to the @ symbol
    end_pt = email + strLength;         //Creates a pointer to the end of the array
    //Error 1: Name
    //
    //Compute length of the name, area before '@'
    if(at_index > 0)
    {
        nameLen = at_index;
    }
    else
    {
        nameLen = strLength - 4;  // in the case the @ symbol is missing, the name goes to last char in domain.
    }
    //1.1 Exists
    if(*email == '@' || nameLen == 0)
    {
         printf(ERROR_04_EMAIL_MISSING_NAME);  // example @domain.com
         return 0;
    }
    //1.2 must start with a char
    if(IsAlpha(*email) != 1)
    {
        printf(ERROR_05_EMAIL_START_INVALID);
        return 0;
    }
    //1.3 contains max 32 chars
    if(nameLen > MAX_EMAIL_LEN)
    {
        printf(ERROR_06_EMAIL_NAME_LEN_INVALID);
        return 0;
    }
        
    //1.4 only contains letters and digits
    for(int i = 0 ; i < nameLen ; i++){
        if((IsDigit(*(email+i)) != 1) && (IsAlpha(*(email+i)) != 1))
        {
            printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
            return 0;
        } 
    }

    //Error 2: @ Symbol
    //

    //2.1 Exists
    if(at_index < 0)
    {
        printf(ERROR_08_EMAIL_MISSING_SYMBOL); // example mike.wisc.edu
        return 0;
    }
       
    //Error 3: Domain Name
    //
    char *domain_firstPT = at_pt + 1;

    char *domain_lastPT = end_pt - 4;

    if((Equals(domain_lastPT, edu, 4) != 1) && (Equals(domain_lastPT, com, 4) != 1) && (Equals(domain_lastPT, net, 4) != 1)){
        domain_lastPT = end_pt;
    }

    //3.1 Exists
    if((domain_lastPT == domain_firstPT) || (end_pt  == domain_firstPT))
    {
        printf(ERROR_09_EMAIL_MISSING_DOMAIN); // example mike@.edu
        return 0;
    }
        
    //3.2 Max of 64 chars 
    if((int)(domain_lastPT - domain_firstPT) > MAX_DOMAIN_LEN)
    {
        printf(ERROR_10_EMAIL_DOMAIN_LEN_INVALID);
        return 0;
    }
  
    //3.4 Subdomains must begin with letter
    //3.3 Composed of one or more subdomains separated by '.'

    //First character after '@' must be a letter
    if(IsAlpha(*domain_firstPT) != 1)
    {
        printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
        return 0;
    }

   //Checks all chars in the domain, if a period is found, it evaluates the next char to ensure it is a letter 
    for(; domain_firstPT != domain_lastPT ; domain_firstPT++){
       if(*domain_firstPT == '.' )
       {
           if(IsAlpha(*(domain_firstPT+1)) != 1)
           {
               printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
               return 0;
           }
       }
    }
   
    domain_firstPT = at_pt + 1;
    
    //3.5 Subdomains can only contain letters and digits
    for(; domain_firstPT != domain_lastPT; domain_firstPT++){
        if((IsDigit(*domain_firstPT) != 1) && (IsAlpha(*domain_firstPT) != 1) && (*domain_firstPT != '.'))
        {
            printf(ERROR_12_EMAIL_DOMAIN_CHARS_INVALID);
            return 0;
        }
    }

    domain_firstPT = at_pt + 1;

    //Error 4: Top-Level Domain
    //

    //4.1 Must be {.edu, .com, .net}

    //Determines if top level domain = ".edu", ".com", or ".net" 
     if((Equals(domain_lastPT, edu, 4) != 1) && (Equals(domain_lastPT, com, 4) != 1) && (Equals(domain_lastPT, net, 4) != 1))
    {
         printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
         return 0;
    }
      /* END MODIFYING CODE HERE */ 
    printf(SUCCESS_2_EMAIL);
    return 1;
}

/*
 * The following password requirements must be verified:
 *  - May use any character except spaces (i.e., "my password" is invalid)
 *  - Must contain at least 8 characters (i.e., "Password" has 8 characters 
 *    and is valid)
 *  - May have at most 16 characters (i.e., "1234567890Abcdef" has 16 
 *    characters and is valid)
 *  - Must contain at least one upper case character [A-Z]
 *  - Must contain at least one lower case character [a-z]
 *
 * @param pwd : The original password string
 * @param len : Size of the original password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Password(char pwd[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    int pwLength = Length(pwd, len);

    //Error 1: May use any character besides spaces
    //
    for(int i = 0 ; i< pwLength; i++){
        if(pwd[i] == ' ')
        {
            printf(ERROR_14_PWD_SPACES_INVALID);
            return 0;
        }
    }
    //Error 2: Must contain at least 8 characters
    //
    if(pwLength < MIN_PASSWORD_LEN)
    {
        printf(ERROR_15_PWD_MIN_LEN_INVALID);
        return 0;
    }  
    //Error 3: Must have at most 16 characters
    //
    if(pwLength > MAX_PASSWORD_LEN)
    {
        printf(ERROR_16_PWD_MAX_LEN_INVALID);
        return 0;
    }
    //Error 4: Must contain atleast 1 uppercase and 1 lowercase letter 
    //
    int hasUpper = 0, hasLower = 0;
    for(int i = 0 ; i < pwLength ; i++){
        if(pwd[i] >= 'A' && pwd[i] <= 'Z')
        {
            hasUpper = 1;    
        }
        if(pwd[i] >= 'a' && pwd[i] <= 'z')
        {
            hasLower = 1;
        }
    }
    if(hasUpper != 1)
    {
        printf(ERROR_17_PWD_MIN_UPPER_INVALID);
        return 0;
    }
    if(hasLower != 1)
    {
        printf(ERROR_18_PWD_MIN_LOWER_INVALID);
        return 0;
    }
    /* END MODIFYING CODE HERE */
    return 1;
}
/*
 * Original Password and the Reentered Password must match
 *
 * @param pwd1 : The original password string
 * @param len1 : Size of the original password input buffer
 * @param pwd2 : The reentered password string
 * @param len2 : Size of the renetered password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Passwords_Match(char pwd1[], size_t len1, char pwd2[], size_t len2) {

    /* BEGIN MODIFYING CODE HERE */
    int pwd1Len = Length(pwd1, len1);
    int pwd2Len = Length(pwd2, len2);
    if((Equals(pwd1, pwd2, pwd1Len) != 1) || (pwd1Len != pwd2Len))
    {
        printf(ERROR_19_PWD_MATCH_INVALID);
        return 0;
    }
       /* END MODIFYING CODE HERE */

    printf(SUCCESS_3_PASSWORDS);
    return 1;
}

/******************************************************************************
 * I/O functions
 *****************************************************************************/

/*
 * Prompts user with an input and reads response from stdin
 *
 * @param message : Prompt displayed to the user
 * @param data : char array to hold user repsonse
 * @param MAX_LENGTH : Size of user response input buffer
 */
void Get_User_Data(char *message, char *data, const int MAX_LENGTH) {
    printf("%s", message);
    fgets(data, MAX_LENGTH, stdin);
    /* BEGIN MODIFYING CODE HERE */
    for(int i = 0; i < Length(data, MAX_LENGTH); i++){
        if(*(data+i) == '\n'){
            *(data+i) = '\0';
        }
    }
    /* END MODIFYING CODE HERE */
    return;

}

