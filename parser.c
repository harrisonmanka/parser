/**
 * parser.c - recursive descent parser for a simple expression language.
 * Most of the functions in this file model a non-terminal in the
 * grammar listed below
 * Author: Harrison Manka
 * Date:   Modified 04/27/23
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "tokenizer.h"
#include "parser.h"
#include "interpreter.h"
#include <math.h>
#include <ctype.h>

/** global line pointer to line of input */
extern char* line;

/** global index in line of input */
extern int j;

/** boolean to tell whether we are missing ')' */
int error_tok;

/**
 * <bexpr> ::= <expr> ;
 * <expr> ::=  <term> <ttail>
 * <ttail> ::=  <add_sub_tok> <term> <ttail> | e
 * <term> ::=  <stmt> <stail>
 * <stail> ::=  <mult_div_tok> <stmt> <stail> | e
 * <stmt> ::=  <factor> <ftail>
 * <ftail> ::=  <compare_tok> <factor> <ftail> | e
 * <factor> ::=  <expp> ^ <factor> | <expp>
 * <expp> ::=  ( <expr> ) | <num>
 * <add_sub_tok> ::=  + | -
 * <mul_div_tok> ::=  * | /
 * <compare_tok> ::=  < | > | <= | >= | != | ==
 * <num> ::=  {0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9}+
 */

/**
 * <bexpr> -> <expr>
 * The function for the non-terminal <bexpr> that
 * goes into non-terminal <expr>
 * @param token: current token array
 * @return: the number of the evaluated expression or an error
 */
int bexpr(char* token){
    int subtotal = expr(token);
    if(subtotal == L_ERROR || subtotal == S_ERROR){
        return subtotal;
    }
    else if(error_tok){
        return S_ERROR;
    }
    else if((!strncmp(token, ";", 1))){
            return subtotal;
    }
    strcpy(token, ";");
    return S_ERROR;

}

/**
 * <expr> -> <term> <ttail>
 * The function for the non-terminal <expr> that views
 * the expression as a series of terms and addition and
 * subtraction operators.
 * @param token: current token array
 * @return: the number of the evaluated expression or an error
 */
int expr(char *token)
{
   int subtotal = term(token);
   if (subtotal == L_ERROR || subtotal == S_ERROR)
      return subtotal;
   else
      return ttail(token, subtotal);
}

/**
 * <ttail> -> <add_sub_tok> <term> <ttail> | e
 * The function for the non-terminal <ttail> that is the
 * the rest of an arithmetic expression after the initial
 * term. So it expects an addition or subtraction operator
 * first or the empty string. 
 * @param token: current token array
 * @param subtotal: the number we have evaluated up to this
 *                  point
 * @return: the number of the evaluated expression or an error
 */
int ttail(char *token, int subtotal)
{
   int term_value;

   if (!strncmp(token, "+", 1)){
      add_sub_tok(token);
      term_value = term(token);
      if (term_value == L_ERROR || subtotal == S_ERROR) {
          return term_value;
      }
      else {
          return ttail(token, (subtotal + term_value));
      }
   }
   else if(!strncmp(token, "-", 1)){
      add_sub_tok(token);
      term_value = term(token);
      if (term_value == L_ERROR || subtotal == S_ERROR) {
          return term_value;
      }
      else {
          return ttail(token, (subtotal - term_value));
      }
   }
   else{
       return subtotal;
   }
}
/**
 * <term> ==> <stmt> <stail>
 * The function for the non-terminal <term> that goes
 * into the non-terminals <stmt> <stail>
 * @param token current token array
 * @return the number of the evaluated expression or an error
 */
int term(char* token){
    int subtotal = stmt(token);
    if (subtotal == L_ERROR || subtotal == S_ERROR)
        return subtotal;
    else
        return stail(token, subtotal);
}

/**
 * <stmt> ==> <factor> <ftail>
 * The function for the non-terminal <term> that goes
 * into the non-terminals <stmt> <stail>
 * @param token current token array
 * @return the number of the evaluated expression or an error
 */
int stmt(char* token){
    int subtotal = factor(token);
    if (subtotal == L_ERROR || subtotal == S_ERROR)
        return subtotal;
    else
        return ftail(token, subtotal);
}

/**
 * <stail> -> <mult_sub_tok> <term> <ttail> | e
 * The function for the non-terminal <stail> that is the
 * the rest of an arithmetic expression after the initial
 * term. So it expects a multiplication or division operator
 * first or the empty string.
 * @param token: current token array
 * @param subtotal: the number we have evaluated up to this
 *                  point
 * @return: the number of the evaluated expression or an error
 */
int stail(char* token, int subtotal){
    int term_value;

    if (!strncmp(token, "*", 1)){
        mul_div_tok(token);
        term_value = stmt(token);
        if (term_value == L_ERROR || subtotal == S_ERROR)
            return term_value;
        else
            return stail(token, (subtotal * term_value));
    }
    else if(!strncmp(token, "/", 1)){
        mul_div_tok(token);
        term_value = stmt(token);
        if (term_value == L_ERROR || subtotal == S_ERROR) {
            return term_value;
        }
        else {
            return stail(token, (subtotal / term_value));
        }
    }
    else {
        return subtotal;
    }
}

/**
 * <factor> ==> <expp> ^ <factor> | <expp>
 * The function for the non-terminal <factor> that goes
 * into the non-terminal <expp> and <factor> again
 * if a ^ operator is found in between them, if not, it goes
 * into <expp>
 * @param token current token array
 * @return the number of the evaluated expression or an error
 */
int factor(char* token){
    int subtotal, term_value, term_value2;
    term_value = expp(token);
    if (!strncmp(token, "^", 1)){
        expon_tok(token);
        term_value2 = factor(token);

        if(term_value == L_ERROR || term_value2 == L_ERROR ||
            term_value2 == S_ERROR || term_value2 == S_ERROR){
            return term_value;
        }
        else{
            subtotal = pow(term_value, term_value2);
            return subtotal;
        }
    }
    else{
        return term_value;
    }
}

/**
 * <ftail> -> <compare_tok> <factor> <ftail> | e
 * The function for the non-terminal <ftail> that is the
 * the rest of an arithmetic expression after the initial
 * term. So it expects a comparison operator
 * first or the empty string.
 * @param token: current token array
 * @param subtotal: the number we have evaluated up to this
 *                  point
 * @return: the number of the evaluated expression or an error
 */
int ftail(char* token, int subtotal){
    int term_value;

    if (!strncmp(token, "<", 1)){
        compare_tok(token);
        term_value = factor(token);
        if (term_value == L_ERROR || term_value == S_ERROR)
            return term_value;
        else
            return ftail(token, (subtotal < term_value));
    }
    else if(!strncmp(token, ">", 1)){
        compare_tok(token);
        term_value = factor(token);
        if (term_value == L_ERROR || term_value == S_ERROR)
            return term_value;
        else
            return ftail(token, (subtotal > term_value));
    }
    else if (!strncmp(token, "<=", 1)){
        compare_tok(token);
        term_value = factor(token);
        if (term_value == L_ERROR || term_value == S_ERROR)
            return term_value;
        else
            return ftail(token, (subtotal <= term_value));
    }
    else if(!strncmp(token, ">=", 1)){
        compare_tok(token);
        term_value = factor(token);
        if (term_value == L_ERROR || term_value == S_ERROR)
            return term_value;
        else
            return ftail(token, (subtotal >= term_value));
    }
    else if (!strncmp(token, "!=", 1)){
        compare_tok(token);
        term_value = factor(token);
        if (term_value == L_ERROR || term_value == S_ERROR)
            return term_value;
        else
            return ftail(token, (subtotal != term_value));
    }
    else if(!strncmp(token, "==", 1)){
        compare_tok(token);
        term_value = factor(token);
        if (term_value == L_ERROR || term_value == S_ERROR)
            return term_value;
        else
            return ftail(token, (subtotal == term_value));
    }
    else {
        return subtotal;
    }
}

/**
 * <expp> ==> ( <expr> ) | <num>
 * The function for the non-terminal <factor> that checks
 * for ( and will go into <expr> and look for ), if not,
 * it will go into <num> and evaluate current token
 * @param token current token array
 * @return the number of the evaluated expression or an error
 */
int expp(char* token){
    if (!strncmp(token, "(", 1)){
        get_token(token);
        int term_value = expr(token);

        if (!strncmp(token, ")", 1)) {
            get_token(token);
            return term_value;
        }
        else {
            error_tok = 1;
            strcpy(token, ")");
            return S_ERROR;
        }
    }
    else {
        return num(token);
    }
}

/**
 * Helper method that calls get_token(token)
 * @param token current token array
 */
void add_sub_tok(char* token){
    get_token(token);
}

/**
 * Helper method that calls get_token(token)
 * @param token current token array
 */
void mul_div_tok(char* token){
    get_token(token);
}

/**
 * Helper method that calls get_token(token)
 * @param token current token array
 */
void compare_tok(char* token){
    get_token(token);
}

/**
 * Helper method that calls get_token(token)
 * @param token current token array
 */
void expon_tok(char* token){
    get_token(token);
}

/**
 *
 * @param token current token array
 * @return the number of the evaluated token or an error
 */
int num(char* token){
    if(is_number(token) == TRUE){
        int temp = atoi(token);
        get_token(token);
        return temp;
    }
    return L_ERROR;
}

/**
 * Helper method to determine if token contains an
 * integer or not
 * @param token current token array
 * @return integer representing true (1) or false (0)
 */
int is_number(char* token){
    return isdigit(*token);
}