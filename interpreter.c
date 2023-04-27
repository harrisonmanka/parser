#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"
#include "interpreter.h"
#include "parser.h"
#include <stdlib.h>

/** global line pointer to input */
char* line;
/** array for holding error 'tokens' */
//char* error;
extern int j;

char* error_tok;

int main(int argc, char* argv[]){
    FILE* in_file = NULL;
    FILE* out_file = NULL;
    char  token[TSIZE];
    char  input_line[LINE];
    int result = 0;
    j = 0;

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
        result = bexpr(token);
        fprintf(out_file, "%s", line);
        if(result == L_ERROR){
            fprintf(out_file, "===> ''\nLexical Error: not a lexeme\n"); //make char* erorr
        }
        else if(result == S_ERROR){
            fprintf(out_file, "===> '' expected\nSyntax Error\n");
        }
        else{
            fprintf(out_file, "Syntax OK\n Value is %d", result);
        }
        j = 0;
    }
}