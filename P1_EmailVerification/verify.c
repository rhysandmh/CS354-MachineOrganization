/******************************************************************************
 * @file: verify.c
 *
 * Main file that prompts user for username, email and password text entries
 * and validates the responses. 
 *
 * @creator: Michael Doescher (mdoescher@wisc.edu)
 * @modified: 9/7/21 Bujji Setty (selagamsetty@wisc.edu)
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE
 *
 *****************************************************************************/

#include <stdio.h>
#include "functions.h"

#define USER_NAME_LENGTH            256
#define EMAIL_LENGTH                512
#define PASSWORD_LENGTH             256

// User Prompts
#define PROMPT_1_USERNAME           "Enter username: "
#define PROMPT_2_EMAIL              "Enter email address: "
#define PROMPT_3_ORIGINAL_PASSWORD  "Enter password: "
#define PROMPT_4_CONFIRM_PASSWORD   "Confirm password: "

int main(){
    char username[USER_NAME_LENGTH];
    char email[EMAIL_LENGTH];
    char password_1[PASSWORD_LENGTH];
    char password_2[PASSWORD_LENGTH];

    Get_User_Data(PROMPT_1_USERNAME, username, USER_NAME_LENGTH);
    if (!Verify_Username(username, USER_NAME_LENGTH)) { return 0; }
    
    Get_User_Data(PROMPT_2_EMAIL, email, EMAIL_LENGTH);
    if (!Verify_Email(email, EMAIL_LENGTH)) { return 0; }

    Get_User_Data(PROMPT_3_ORIGINAL_PASSWORD, password_1, PASSWORD_LENGTH);
    if (!Verify_Password(password_1, PASSWORD_LENGTH)) { return 0; }

    Get_User_Data(PROMPT_4_CONFIRM_PASSWORD, password_2, PASSWORD_LENGTH); 
    if (!Verify_Passwords_Match(password_1, PASSWORD_LENGTH, 
                                password_2, PASSWORD_LENGTH)) { return 0; }
    return 0;
}

