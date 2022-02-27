/***************************************************************
  Student Name: Collin Lowing
  File Name: main.c
  Project 2

  runs the rest of the program
***************************************************************/

#include <stdio.h>
#include "RDParser.h"

int main(int argc, char** argv) {
    if(argc == 2)
    {
        char* filename = argv[1]; // get filename from command line arguments

        init(filename);

        parse();
    }
    else
    {
        printf("program was expecting a command line argument\n");
        return 1;
    }

    return 0;
}
