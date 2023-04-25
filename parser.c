/*
 * parser.c - recursive descent parser for a simple expression language.
 * Most of the functions in this file model a non-terminal in the
 * grammar listed below
 * @author Harrison Manka & Matthew Agudelo
 * Date: 4/21/23
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "tokenizer.h"
#include "parser.h"

extern char *token;



/*
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
 * <expr> -> <term> <ttail>
 * The function for the non-terminal <expr> that views
 * the expression as a series of terms and addition and
 * subtraction operators.
 * @param token: the line being read
 * @return: the number of the evaluated expression or an error
 */
int expr(char *token)
{
   int subtotal = term(token);
   token = get_token(token);
   if (subtotal == ERROR)
      return subtotal;
   else
      return ttail(token, subtotal);
}

/**
 * <term> ::=  <stmt> <stail>
 * The function for the non-terminal <term> that views
 * the expression as a series of terms and multiplication and
 * division operators.
 * @param token: the line being read
 * @return: the number of the evaluated expression or an error
 */
int term(char *token)
{
   int subtotal = stmt(token);
   //token = get_token(token);
   if (subtotal == ERROR)
      return subtotal;
   else
      return stail(token, subtotal);
}

/**
 * <stmt> ::=  <factor> <ftail>
 * The function for the non-terminal <term> that views
 * the expression as a series of terms and multiplication and
 * division operators.
 * @param token: the line being read
 * @return: the number of the evaluated expression or an error
 */
int stmt(char *token)
{
   int subtotal = factor(token);
   token = get_token(token);
   if (subtotal == ERROR)
      return subtotal;
   else
      return ftail(token, subtotal);
}


/**
 * <ttail> -> <term> <ttail> | e
 * The function for the non-terminal <ttail> that is the
 * the rest of an arithmetic expression after the initial
 * term. So it expects an addition or subtraction operator
 * first or the empty string. 
 * @param token: the line being read
 * @param subtotal: the number we have evaluated up to this
 *                  point
 * @return: the number of the evaluated expression or an error
 */
int ttail(char *token, int subtotal)
{
   int term_value;

   if (!strncmp(token, "+", 1))
   {
      //token = get_token(token);
      term_value = term(get_token(token));

      // if term returned an error, give up otherwise call ttail
      if (term_value == ERROR){
         return term_value;
      }
      else{
         //token = get_token(token);
         return ttail(get_token(token), (subtotal + term_value));
      }
   }
   else if(!strncmp(token, "-", 1))
   {
      //token = get_token(token);
      term_value = term(get_token(token));

      // if term returned an error, give up otherwise call ttail
      if (term_value == ERROR){
         return term_value;
      }
      else{
         //token = get_token(token);
         return ttail(get_token(token), (subtotal - term_value));
      }
   }
   else if (isspace(*token))
   {
      //token = get_token(token);
      return ttail(get_token(token), subtotal);
   }
   /* empty string */
   else
      return subtotal;
}

/**
 * <stail> ::=  <stmt> <stail> | e
 * The function for the non-terminal <ttail> that is the
 * the rest of an arithmetic expression after the initial
 * term. So it expects an addition or subtraction operator
 * first or the empty string. 
 * @param token: the line being read
 * @param subtotal: the number we have evaluated up to this
 *                  point
 * @return: the number of the evaluated expression or an error
 */
int stail(char *token, int subtotal)
{
   //token = get_token(token);
   int term_value;

   if (!strncmp(token, "*", 1))
   {
      token = get_token(token);
      term_value = term(token);
      token = get_token(token);

      // if term returned an error, give up otherwise call stail
      if (term_value == ERROR)
         return term_value;
      else
         return stail(token, (subtotal * term_value));
   }
   else if(!strncmp(token, "/", 1))
   {
      token = get_token(token);
      term_value = term(token);
      token = get_token(token);

      // if term returned an error, give up otherwise call stail
      if (term_value == ERROR)
         return term_value;
      else
         return stail(token, (subtotal / term_value));
   }
   else if (isspace(*token))
   {
      token = get_token(token);
      return stail(token, subtotal);
   }   
   /* empty string */
   else
      return subtotal;
}

/**
 * <ftail> ::=  <factor> <ftail> | e
 * The function for the non-terminal <ttail> that is the
 * the rest of an arithmetic expression after the initial
 * term. So it expects an addition or subtraction operator
 * first or the empty string. 
 * @param token: the line being read
 * @param subtotal: the number we have evaluated up to this
 *                  point
 * @return: the number of the evaluated expression or an error
 */
int ftail(char *token, int subtotal)
{
   int term_value;
   //token = get_token(token);

   if (!strncmp(token, ">", 1))
   {
      token = get_token(token);
      term_value = factor(token);
      token = get_token(token);

      // if term returned an error, give up otherwise call ftail
      if (term_value == ERROR)
         return term_value;
      else
         return ftail(token, (subtotal > term_value));
   }
   else if (!strncmp(token, ">=", 2))
   {
      token = get_token(token);
      term_value = factor(token);
      token = get_token(token);

      // if term returned an error, give up otherwise call ftail
      if (term_value == ERROR)
         return term_value;
      else
         return ftail(token, (subtotal >= term_value));
   }
   else if(!strncmp(token, "<", 1))
   {
      token = get_token(token);
      term_value = factor(token);
      token = get_token(token);

      // if term returned an error, give up otherwise call ftail
      if (term_value == ERROR)
         return term_value;
      else
         return ftail(token, (subtotal < term_value));
   }
   else if(!strncmp(token, "<=", 2))
   {
      token = get_token(token);
      term_value = factor(token);
      token = get_token(token);

      // if term returned an error, give up otherwise call ftail
      if (term_value == ERROR)
         return term_value;
      else
         return ftail(token, (subtotal <= term_value));
   }
   else if(!strncmp(token, "==", 2))
   {
      token = get_token(token);
      term_value = factor(token);
      token = get_token(token);

      // if term returned an error, give up otherwise call ftail
      if (term_value == ERROR)
         return term_value;
      else
         return ftail(token, (subtotal == term_value));
   }
   else if (!strncmp(token, "^", 1))
   {
      token = get_token(token);
      return pow(subtotal,factor(token));
   }
   else if(!strncmp(token, ";", 1)){
      return subtotal;
   }
   else if(!strncmp(token, "\n", 1)){
      return subtotal;
   }
   else if (isspace(*token))
   {
      token = get_token(token);
      return ftail(token, subtotal);
   }
   /* empty string */
   else
      return subtotal;
}

/**
 * <factor> ::=  <expp> ^ <factor> | <expp>
 * The function for the non-terminal <ttail> that is the
 * the rest of an arithmetic expression after the initial
 * term. So it expects an addition or subtraction operator
 * first or the empty string. 
 * @param token: the line being read
 * @return: the number of the evaluated expression or an error
 */
int factor(char *token)
{
   int term_value;
   //char *temp_token;

   if (!strncmp(token, "^", 1))
   {
      token = get_token(token);
      term_value = expp(token);
      token = get_token(token);
      return pow(term_value,expp(token));    
   }
   else if (isspace(*token))
   {
      token = get_token(token);
      if(isdigit(*token)){
         
         term_value = expp(token);
         token = get_token(token);
         if(!strncmp(token,";",1)){
            return term_value;
         }

         return pow(term_value,expp(token));
      }

      token = get_token(token);
      return factor(token);
   }  
   else if (isdigit(*token))
   {
      return expp(token);
   } 
   return expp(token);
}

/**
 * <expp> ::=  ( <expr> ) | <num>
 * The function for the non-terminal <ttail> that is the
 * the rest of an arithmetic expression after the initial
 * term. So it expects an addition or subtraction operator
 * first or the empty string. 
 * @param token: the line being read
 * @param subtotal: the number we have evaluated up to this
 *                  point
 * @return: the number of the evaluated expression or an error
 */
int expp(char *token)
{
   int term_value;
   char *digit;


   if (!strncmp(token, "(", 1))
   {
      token = get_token(token);
      term_value = expr(token);

      // if term returned an error, give up otherwise call ttail
      if (term_value == ERROR)
         return term_value;
      else
         return expp(token);
   }
   else if (isspace(*token))
   {
      token = get_token(token);
      return expp(token);
   } 
   else if (!strncmp(token, "^", 1))
   {
      token = get_token(token);
      if(isdigit(*token)){
         term_value = expp(token);
         token = get_token(token);
         return pow(term_value,expp(token));
      }

      return expp(token);
   }
      else if (!strncmp(token, ")", 1))
   {
      //token = get_token(token);
      return expp(get_token(token));
   }   
   /* check if value is a digit */
   else{
      
      if (isdigit(*token))
      {
         digit = token;
         //token = get_token(token);
         get_token(token);
         //because the value is saved as an ascii character this gets its actual numeric value
         return *digit - '0';
      }
      return ERROR;      
   }
}