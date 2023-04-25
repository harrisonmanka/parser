#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"
#include "parser.h"
extern char *line;
extern int count;

/**
 * tokenizer.c - A simple token recognizer.
 *
 * NOTE: The terms 'token' and 'lexeme' are used interchangeably in this
 *       program.
 *
 * @author Harrison Manka & Matthew Agudelo
 * @version 1
 * @date 4/21/23
 */
int main(int argc, char* argv[]) {
   //char  *token[TSIZE];      /* Spot to hold a token, fixed size */
   char  input_line[LINE];     /* Line of input, fixed size        */
   FILE  *in_file = NULL;      /* File pointer                     */
   FILE  *out_file = NULL;
   int   line_count;           /* Number of lines read             */

  if (argc != 3) {
    printf("Usage: tokenizer inputFile outputFile\n");
    exit(1);
  }

  in_file = fopen(argv[1], "r");
  if (in_file == NULL) {
    fprintf(stderr, "ERROR: could not open %s for reading\n", argv[1]);
    exit(1);
  }

  out_file = fopen(argv[2], "w");
  if (out_file == NULL) {
    fprintf(stderr, "ERROR: could not open %s for writing\n", argv[2]);
    exit(1);
  }
int cnt = 1;
//Main while loop that loops through the text file line by line and outputs the lexemes.
  while (fgets(input_line, LINE, in_file) != NULL){ 
    int i = 0;            //counter for each char in the file
    line = input_line;    //assign line from text file to global var line
    line_count++;
    fprintf(out_file,"%s", line);
   
    count = 0;            //initialize our token counter to 0
    get_token(line); 
    expr(line); 
      
     if(expr(line) == ERROR)
    {
    fprintf(out_file,"%s%d%s", "ERROR ", expr(line), " not valid lexeme \n" );
    }
    else{
      fprintf(out_file, "%s%s%d\n", "Syntax is Ok\n","Value is ", expr(line));
    }
  
   

    cnt++;
    fprintf(out_file,"%s\n\n", "------------------------");
    
    
    //while loop to get each char to see if its null character or semi-colon
    //if the char is either of these characters get the next character.
    while (line[i] != '\0' && line[i] != ';' &&  line[i] != EOF){
      if(line[i] != '\n'){
        fgets(input_line, LINE, in_file);
        line = input_line;
        line_count++;
        i = 0;            //initalize loop counter to 0 because we are grabbing a new line
        count = 0;        //set count to 0 because we are starting on a new line
        //get_token(line);
        
        expr(line);
        
        cnt++;
      }
      i++;
    }
  }

   //Close out the input and output files
   fclose(in_file);
   fclose(out_file);
   return 0;
}
