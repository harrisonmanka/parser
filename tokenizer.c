/**
 * tokenizer.c - A simple token recognizer.
 *
 * NOTE: The terms 'token' and 'lexeme' are used interchangeably in this
 *       program.
 *
 * @author Harrison Manka
 * @date 4/21/2023
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"
#include "interpreter.h"

// global variables
//char *line;             // Global pointer to line of input
// (optional) can declare some additional variable if you want to
char *token_type = "";
//char *grammar = "";
extern char* line;
int j;
/**
* add comment
*/
//int main(int argc, char* argv[]) {
//    char  token[TSIZE];      /* Spot to hold a token, fixed size */
//    char  input_line[LINE];  /* Line of input, fixed size        */
//    FILE  *in_file = NULL;        /* File pointer                     */
//    FILE  *out_file = NULL;
//    int   line_count = 0;        /* Number of lines read             */
//    //start,    /* is this the start of a new statement? */
//    int count = 0;             /* count of tokens                  */
//
//    if (argc != 3) {
//        printf("Usage: tokenizer inputFile outputFile\n");
//        exit(1);
//    }
//
//    in_file = fopen(argv[1], "r");
//    if (in_file == NULL) {
//        fprintf(stderr, "ERROR: could not open %s for reading\n", argv[1]);
//        exit(1);
//    }
//
//    out_file = fopen(argv[2], "w");
//    if (out_file == NULL) {
//        fprintf(stderr, "ERROR: could not open %s for writing\n", argv[2]);
//        exit(1);
//    }
//    while (fgets(input_line, LINE, in_file) != NULL)
//    {
//        line = input_line;
//        if(line_count == 0){
//            line_count++;
//            fprintf(out_file, "Statement #" "%d \n", line_count);
//            line_count++;
//        }
//        while(line[j] != '\0'){
//            get_token(token);
//            get_token_type(token);
//            //print_to_file(out_file, token, count);
//            count++; //lexeme count
//            memset(token, 0, sizeof(token));
//            if(line[j] == '\n'){
//                fprintf(out_file,"%s", "-----------------------------------------------\n");
//                fprintf(out_file, "Statement #" "%d \n", line_count);
//                count = 0;
//                line_count++;
//                line++;
//            }
//            else if(line[j] == '\t'){
//                j++;
//            }
//            else if(line[j] == ';'){
//                get_token(token);
//                token_type = "SEMI_COLON";
//                //print_to_file(out_file, token, count);
//                fprintf(out_file,"%s", "-----------------------------------------------\n");
//                fprintf(out_file, "Statement #" "%d \n", line_count);
//                line_count++; //statement number
//                count = 0; //token #
//                memset(token, 0, sizeof(token));
//            }
//        }
//        j = 0;
//    }
//    fclose(in_file);
//    fclose(out_file);
//    return 0;
//}

/**
* grab token
*/
void get_token(char *token_ptr){
    int i = 0;
    while(line[j] == ' ' || line[j] == '\t'){
        j++;
    }

    //check current line pointer
    if(isdigit(line[j])){
        token_ptr[i] = line[j];
        i++; j++;
        //check for next number(s)
        while(isdigit(line[j])){
            token_ptr[i] = line[j];
            i++; j++;
        }
    }
    else if(isalpha(line[j])){
        token_ptr[i] = line[j];
        i++; j++;
        //check for next number(s)
        while(isalpha(line[j])){
            token_ptr[i] = line[j];
            i++; j++;
        }
    }
    else if (((line[j] == '<')&&(line[j+1] == '=')) || ((line[j] == '>')&&(line[j+1] == '='))
            || ((line[j] == '!')&&(line[j+1] == '=')) || ((line[j] == '=')&&(line[j+1] == '='))) {
        token_ptr[i] = line[j];
        token_ptr[i+1] = line[j+1];
        j++;
    }
    else if ((line[j] == '*') || (line[j] == ';') || (line[j] == '(') ||
             (line[j] == ')') || (line[j] == '+') || (line[j] == '-') ||
             (line[j] == '^') || (line[j] == '/') || (line[j] == ';')){
        token_ptr[i] = line[j];
        j++;
    }
    else{
        token_ptr[i] = line[j];
        j++;
    }
}
/**
 *
 * @param out_file
 * @param token_arr
 * @param token_type
 */
//void print_to_file(FILE* out_file, char* token_arr, int count){
//    if(!(strcmp(token_type, "ERROR"))) {
//        fprintf(out_file, "===> '%s'\nLexical error: not a lexeme\n", token_arr);
//    }
//    else{
//        fprintf(out_file, "Lexeme " "%d" " is " "%s" " and is a " "%s\n", count, token_arr, grammar, token_type);
//    }
//}

/**
 * get token type
 */
void get_token_type(char* token){
    if(strcmp(token, ADD_OP) == 0) {
        token_type = "ADD_OP";
        //grammar = "an";
    }
    else if (strcmp(token, SUB_OP) == 0) {
        token_type = "SUB_OP";
        //grammar = "a";
    }
    else if (strcmp(token, MULT_OP) == 0) {
        token_type = "MULT_OP";
        //grammar = "a";
    }
    else if (strcmp(token, DIV_OP) == 0) {
        token_type = "DIV_OP";
        //grammar = "a";
    }
    else if (strcmp(token, LEFT_PAREN) == 0) {
        token_type = "LEFT_PAREN";
        //grammar = "a";
    }
    else if (strcmp(token, RIGHT_PAREN) == 0){
        token_type = "RIGHT_PAREN";
        //grammar = "a";
    }
    else if (strcmp(token, EXPON_OP) == 0) {
        token_type = "EXPON_OP";
        //grammar = "an";
    }
    else if (strcmp(token, ASSIGN_OP) == 0) {
        token_type = "ASSIGN_OP";
        //grammar = "an";
    }
    else if (strcmp(token, LESS_THEN_OP) == 0) {
        token_type = "LESS_THEN_OP";
        //grammar = "a";
    }
    else if (strcmp(token, LESS_THEN_OR_EQUAL_OP) == 0) {
        token_type = "LESS_THEN_OR_EQUAL_OP";
        //grammar = "a";
    }
    else if (strcmp(token, GREATER_THEN_OP) == 0) {
        token_type = "GREATER_THEN_OP";
        //grammar = "a";
    }
    else if (strcmp(token, GREATER_THEN_OR_EQUAL_OP) == 0) {
        token_type = "GREATER_THEN_OR_EQUAL_OP";
        //grammar = "a";
    }
    else if (strcmp(token, EQUALS_OP) == 0) {
        token_type = "EQUALS_OP";
        //grammar = "an";
    }
    else if (strcmp(token, NOT_OP) == 0) {
        token_type = "NOT_OP";
        //grammar = "a";
    }
    else if (strcmp(token, NOT_EQUAL_OP) == 0) {
        token_type = "NOT_EQUAL_OP";
        //grammar = "a";
    }
    else if (strcmp(token, SEMI_COLON) == 0) {
        token_type = "SEMI_COLON";
        //grammar = "a";
    }
    else if (isdigit(token[0])){
        token_type = "INT_LITERAL"; //grammar = "an";
    }
    else {
        token_type = "ERROR";
    }
}