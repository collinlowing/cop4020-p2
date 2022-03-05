/***************************************************************
  Student Name: Collin Lowing
  File Name: LexicalAnalyzer.c
  Project 2

  perform lexical analysis on a file
***************************************************************/

#include "LexicalAnalyzer.h"

// declare and initialize global variables
int numLines = 1;
int type;
FILE * input = NULL;
char ch;
char * fName;
char numLexeme[MAX_STR_LENGTH] = "";
char idLexeme[MAX_STR_LENGTH] = "";

// opens file and checks if the file is actually open
void init(char * filename)
{
    // init file input
    fName = filename;
    input = fopen(fName, "r");

    if(input == NULL)
    {
        printf("error: input file could not be open\n");
        exit(1);
    }

    /*// init file output
    char * outputFileName = fName;
    strcat(outputFileName, ".out");

    output = fopen(outputFileName, "w");

    // check if output file is open
    if(output == NULL)
    {
        printf("error: output file could not be opened\n");
        exit(1);
    }
    else
    {
        printf("output file is open\n");
    }*/
}

// handles file i/o and collects identifiers
int lexan()
{
    // initialize local variables
    int numLength = 0;
    int idLength = 0;
    // emptying char arrays
    numLexeme[0] = '\0';
    idLexeme[0] = '\0';

    while(1)
    {
        ch = fgetc(input); // get first char from file
        if (ch == ' ' | ch == '\t') {   // do nothing
            ;                     // whitespace is ignored
        }
        else if(ch == '\n') // increments line number
        {
            numLines++;
        }
        else if (ch == '~') // ignore comments
        {
            while(ch != '\n') //skip over everything in comment line
            {
                ch = fgetc(input);
            }
            ungetc(ch, input);
        }
        else if (isdigit(ch)) // handles numbers
        {
            while(isdigit(ch)) // grabs all digits to number
            {
                append(numLexeme, ch);  // inputs digits into number string
                numLength++;                   // increments number length
                ch = fgetc(input);
            }
            ungetc(ch, input);

            append(numLexeme, ch);      // adds digit to number string
            return NUM;
        }
        else if (isalpha(ch)) // handle identifiers starting with a letter
        {
            while(isalpha(ch) || isdigit(ch) || ch == '.' || ch == '_') {   // letters, numbers, period or underscore can follow the first letter
                if(idLength >= 1 && idLexeme[idLength - 1] == '_' && ch == '_') // checks if two '_' chars are adjacent
                {
                    printf("Line %d error: identifier cannot have more than one '_' adjacent", numLines);
                    cleanup();
                    exit(1);
                }

                append(idLexeme, ch); // add char to identifier string
                idLength++;                  // increment string length

                // check if starts with begin
                if(strcmp(idLexeme, "begin") == 0)
                {
                    return BEGIN;
                }
                // checks if ends with 'end.'
                else if(strcmp(idLexeme, "end.") == 0)
                {
                    return END;
                }
                // checks if primitive type initialization
                else if(strcmp(idLexeme, "int") == 0)
                {
                    return PRIMITIVE;
                }

                ch = fgetc(input); //gets next char
            }
            if(idLength > 0 && idLexeme[idLength - 1] == '_') // checks if identifier ends with '-'
            {
                printf("Line %d error: identifier cannot end with '_'\n", numLines);
                cleanup();
                exit(1);
            }

            type = lookup(idLexeme); // looks in linked list for the identifier and returns its type

            if(type == NOT_FOUND) // if the identifier is not found then add it to the list
            {
                //insert(ID, idLexeme);
                ungetc(ch, input);
                return ID; // return type
            }

            ungetc(ch, input);
            return type;
        }
        else if(ch == EOF) // reached end of file without 'end.'
        {
            printf("Line %d error: expected 'end.'\n", numLines);
            cleanup();
            exit(1);
        }
        else
        {
            // first char is '_'
            if(ch == '_')
            {
                printf("Line %d error: identifier cannot start with '_'", numLines);
                cleanup();
                exit(1);
            }
            return ch; // return the char ascii value if not an identifier or number
        }
    }
}

int lookup(char lexeme[MAX_STR_LENGTH]) {
    // search linked list for lexeme
    struct node* match = find(lexeme);
    // return type of symbol
    if(match == NULL)
    {
        return NOT_FOUND;
    }
    else
        return match->key;
}

// add char to char array or string
void append(char * str, char c)
{
    int length = strlen(str);
    str[length] = c;
    str[length + 1] = '\0';
}