#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"
#include "parser.h"
#include <stdlib.h>

char* line;

int main(int argc, char* argv[]){
    FILE* in_file = null;
    FILE* out_file = null;
    char  token[TSIZE];
    char  input_line[LINE];
    char* final;

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

    while (fgets(input_line, LINE, in_file) != NULL){
        line = input_line;
        get_token(token);
        final = bexpr(token);
    }
}


/**
* Main function to loop through the text file and get each lexeme.
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
}