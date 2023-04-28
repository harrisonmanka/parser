Revised README - 04/27/23
Authors: Harrison Manka

Project 4 --> Interpreter
How to compile & run the program:

  ---> COMPILE: gcc -Wall interpreter.c parser.c tokenizer.c -lm -o interpreter
  ---> RUN: ./interpreter [input_file] [output_file]

Description: This is a simple parsing program where we read input from a text file,
             parse the sentence and execute the expression giving us an integer
             value for the evaluated expression. It will also give us lexical
             and syntactical errors for the sentences that do not have the
             correct syntax or lexemes. The output of these evaluated
             expressions are piped to the output file specified of your choice.
