/**
 * interpreter.c - driver for our parser where we
 * take input and spit out the output of the parsing.
 * @author Harrison Manka
 * @date 04/27/23
 */
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

/** global index to the line of input */
extern int j;

/**
 * Main method that creates two file objects, in and out.
 * Creates a token array to hold one token at a time, and
 * an input_line that is the line of input from fgets.
 * While the file is not equal to null, we grab each line
 * and call get_token then recursively parse our sentence.
 * @param argc
 * @param argv
 * @return 0
 */
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
        if((strcmp(line, "\n"))){
            get_token(token);
            result = bexpr(token);
            fprintf(out_file, "%s", line);
            if(result == L_ERROR){
                fprintf(out_file, "===> '%s'\nLexical Error: not a lexeme\n\n", token);
            }
            else if(result == S_ERROR){
                fprintf(out_file, "===> '%s' expected\nSyntax Error\n\n", token);
            }
            else{
                fprintf(out_file, "Syntax OK\nValue is %d\n\n", result);
            }
        }
        j = 0;
    }
}