/**
 * tokenizer.c - A simple token recognizer.
 *
 * NOTE: The terms 'token' and 'lexeme' are used interchangeably in this
 *       program.
 *
 * @author Harrison Manka
 * @date 4/27/2023
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"
#include "interpreter.h"

/** global line pointer to line of input */
extern char* line;

/** global index in line of input */
int j;

/**
 * get_token method that grabs an individual token
 * or more depending on the token. skips whitespace
 * respectfully
 * @param token_ptr pointer to our token array
 */
void get_token(char *token_ptr){
    int i = 0;
    while(isspace(line[j])){
        j++;
    }
    if(isdigit(line[j])){
        token_ptr[i] = line[j];
        i++; j++;
        while(isdigit(line[j])){
            token_ptr[i] = line[j];
            i++; j++;
        }
        token_ptr[i] = '\0';
    }
    else if(isalpha(line[j])){
        token_ptr[i] = line[j];
        i++; j++;
        //check for next number(s)
        while(isalpha(line[j])){
            token_ptr[i] = line[j];
            i++; j++;
        }
        token_ptr[i] = '\0';
    }
    else if (((line[j] == '<')&&(line[j+1] == '=')) || ((line[j] == '>')&&(line[j+1] == '='))
            || ((line[j] == '!')&&(line[j+1] == '=')) || ((line[j] == '=')&&(line[j+1] == '='))) {
        token_ptr[i] = line[j];
        i++; j++;
        token_ptr[i] = line[j];
        j++; i++;
        token_ptr[i] = '\0';
    }
    else if ((line[j] == '*') || (line[j] == ';') || (line[j] == '(') ||
             (line[j] == ')') || (line[j] == '+') || (line[j] == '-') ||
             (line[j] == '^') || (line[j] == '/') || (line[j] == ';')){
        token_ptr[i] = line[j];
        j++; i++;
        token_ptr[i] = '\0';
    }
    else{
        token_ptr[i] = line[j];
        j++; i++;
        token_ptr[i] = '\0';
    }
}