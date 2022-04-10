/******************************************************************************
 * @file: functions.h
 *
 * Header file for string verification functions.
 *
 * @creator: Bujji Setty (selagamsetty@wisc.edu)
 * @modified: 9/1/21 Asmit Nayak (anayak6@wisc.edu)
 * @modified: 9/11/21 Bujji Setty (selagamsetty@wis.edu)
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE
 *
 *****************************************************************************/

#ifndef PROJECT_FUNCTIONS_H
#define PROJECT_FUNCTIONS_H

// Error Messages
#define ERROR_01_USER_START_INVALID         "Invalid username starting character\n"
#define ERROR_02_USER_LEN_INVALID           "Max 32 charcters\n"
#define ERROR_03_USER_CHARS_INVALID         "Invalid character in username\n"

#define ERROR_04_EMAIL_MISSING_NAME         "Name missing\n"
#define ERROR_05_EMAIL_START_INVALID        "Name must begin with letter\n"
#define ERROR_06_EMAIL_NAME_LEN_INVALID     "Name must have fewer than 32 characters\n"
#define ERROR_07_EMAIL_NAME_CHARS_INVALID   "Invalid character in name\n"
#define ERROR_08_EMAIL_MISSING_SYMBOL       "Missing @\n"
#define ERROR_09_EMAIL_MISSING_DOMAIN       "Domain missing\n"
#define ERROR_10_EMAIL_DOMAIN_LEN_INVALID   "Maximum of 64 characters in domain\n"
#define ERROR_11_EMAIL_DOMAIN_START_INVALID "Domain or subdomain must begin with letter\n"
#define ERROR_12_EMAIL_DOMAIN_CHARS_INVALID "Invalid character in domain\n"
#define ERROR_13_TOP_LEVEL_DOMAIN_INVALID   "Top level domain must be .edu, .com, or .net\n"

#define ERROR_14_PWD_SPACES_INVALID         "Password may not contain spaces\n"
#define ERROR_15_PWD_MIN_LEN_INVALID        "Password must have at least 8 characters\n"
#define ERROR_16_PWD_MAX_LEN_INVALID        "Password may have at most 16 character\n"
#define ERROR_17_PWD_MIN_UPPER_INVALID      "Password must contain at least one upper case character\n"
#define ERROR_18_PWD_MIN_LOWER_INVALID      "Password must contain at least one lower case character\n"

#define ERROR_19_PWD_MATCH_INVALID          "Passwords do not match\n"

// Success Messages
#define SUCCESS_1_USER                      "Username formatting is correct\n"
#define SUCCESS_2_EMAIL                     "Email formatting is correct\n"
#define SUCCESS_3_PASSWORDS                 "Passwords match\n"

void Get_User_Data(char *message, char *data, const int MAX_LENGTH);

int Verify_Username(char user[], size_t len);

int Verify_Email(char email[], size_t len);

int Verify_Password(char pwd[], size_t len);

int Verify_Passwords_Match(char pwd1[], size_t len1, char pwd2[], size_t len2);

#endif //PROJECT_FUNCTIONS_H
