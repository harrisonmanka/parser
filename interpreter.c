#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"
#include "parser.h"
#include <stdlib.h>

char* line;

int main(int argc, char* argv[]){
    FILE* in_file = NULL;
    FILE* out_file = NULL;
    char  token[TSIZE];
    char  input_line[LINE];
    

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
        bexpr(token);
        fprintf(out_file, line);
    }

}