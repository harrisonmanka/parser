/**
 * tokenizer.c - A simple token recognizer. 
 *
 * NOTE: The terms 'token' and 'lexeme' are used interchangeably in this
 *       program.
 *
 * @author Harrison Manka & Matthew Agudelo
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"
#include "parser.h"

// global variables
char *line;             // Global pointer to line of input
char temp_tok[TSIZE];   //Global char array to hold tokens
int count;              //Global counter for number of tokens



/**
* this function takes a line from the input file and parses it to 
*determine if each token is valid according to the rules.
*Parameter -> char *token_ptr: a line from the input file.
*/
//get-token doesn't return anything. move to next token
char* get_token(char *token_ptr){
  int j = 0;            //index variable for array of temporary tokens
  temp_tok[0] = '\0';   //clear first index of array for temporary tokens
  temp_tok[1] = '\0';   //clear second index of array for temporary tokens

  if (isdigit(*token_ptr)){
    temp_tok[j] = *token_ptr;
    j++;
    token_ptr++;

    while(isdigit(*token_ptr)){
      temp_tok[j] = *token_ptr;
      j++;
      token_ptr++;
    }
  }

  else if (*token_ptr == '='){
    temp_tok[j] = *token_ptr;
    token_ptr++;
    j++;
    if(*token_ptr == '='){
      temp_tok[j] = *token_ptr;
      token_ptr++;
    }
  }

  else if (*token_ptr == '!'){
    temp_tok[j] = *token_ptr;
    token_ptr++;
    j++;
    if(*token_ptr == '='){
      temp_tok[j] = *token_ptr;
      token_ptr++;
    }
  }

  else if(*token_ptr == '<'){
    temp_tok[j] = *token_ptr;
    token_ptr++;
    j++;
    if(*token_ptr == '='){
      temp_tok[j] = *token_ptr;
      token_ptr++;
    }
  }

  else if(*token_ptr == '>'){
    temp_tok[j] = *token_ptr;
    token_ptr++;
    j++;
    if(*token_ptr == '='){
      temp_tok[j] = *token_ptr;
      token_ptr++;
    }
  }

  else if(isspace(*token_ptr)){
    token_ptr++;
    get_token(token_ptr);
  }

  //check if the token is a null character then do nothing
  else if(*token_ptr == '\0'){
    //do nothing

  }

  else if(*token_ptr == ';'){
    temp_tok[j] = *token_ptr;
  }

  else if(*token_ptr == '+'){
    temp_tok[j] = *token_ptr;
    token_ptr++;
  }

  else if(*token_ptr == '-'){
  temp_tok[j] = *token_ptr;
  token_ptr++;
  }

  else if(*token_ptr == '/'){
  temp_tok[j] = *token_ptr;
  token_ptr++;
  }

  else if(*token_ptr == '('){
  temp_tok[j] = *token_ptr;
  token_ptr++;
  }

  else if(*token_ptr == ')'){
  temp_tok[j] = *token_ptr;
  token_ptr++;
  }

  else if(*token_ptr == '^'){
  temp_tok[j] = *token_ptr;
  token_ptr++;
  }

  else if(*token_ptr == '*'){
  temp_tok[j] = *token_ptr;
  token_ptr++;

  }
  else{
    temp_tok[j] = *token_ptr;
    token_ptr++;
    get_token(token_ptr);
  }
  return token_ptr;

}

/*
*This function takes a char array of lexemes and prints them out
*and also increases the token counter
 */
void print_lex(char *lex){
  char* id;
  id = id_Expr(lex);
  fprintf(stdout, "%s %d %s %s %s %s\n","Lexeme", count, "is", lex, "and", id);
  count++;      //increas the token counter
}
/**
 * Assigns a idenitfier to the lexeme passed 
 * 
 * @param lex the lexeme that is being used to assign identifier
 * @return char* the identifier of the lexeme passed
 */
char *id_Expr(char *lex){
  char* val[10]; 
  if(*lex == ';'){
    *val = "SEMI_COLON";
  }
  else if(*lex == '+'){
    *val = "PLUS";
  }
  else if(*lex == '-'){
    *val = "MINUS";
  }
  else if(*lex == '*'){
    *val = "MULTI_OP";
  }
  else if(*lex == '/'){
    *val = "DIV_OP";
   }
  else if(*lex == '('){
    *val = "LEFT_PAREN";
    }
  else if(*lex == ')'){
    *val = "RIGHT_PAREN";
     }
  else if(*lex == '^'){
    *val = "EXPON";
  }

  else if(*lex == '='){
    lex++;
     if(*lex == '='){
        *val = "EQUAL_OP";
       }
      else{
         *val = "ASSIGN";
       }
       
       
  }
   else if(*lex == '<'){
     lex++;
     if(*lex == '='){
       *val = "LESS_THAN_EQ";
     }
     else{
         *val = "LESS_THAN";
       }
    
  } 

   else if(*lex == '>'){
     lex++;
       if(strlen(lex) == '='){
       *val = "GREATER_THAN_EQ";
       }
       else{
         *val = "GREATER_THAN_EQ";
       }
  }
   else if(*lex == '!'){
     lex++;
       if(strlen(lex) == '='){
       *val = "NOT_EQ";
       }
       else{
         *val = "NOT_EQ_OP";
       }
  }
   else if(isdigit(*lex)){
    *val = "INT_LITERAL";
  }
  return *val;
}
