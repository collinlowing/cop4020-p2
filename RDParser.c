/***************************************************************
  Student Name: Collin Lowing
  File Name: RDParser.c
  Project 2

  parses a statement found in lexical analysis
***************************************************************/

#include "RDParser.h"

int lookahead;
int paraLeft;
int paraRight;

// starts the parsing and lexical analysis
void parse()
{
    lookahead = lexan();
    // check if starts with begin
    if(lookahead != BEGIN)
    {
        printf("Line %d error: expected 'begin'\n", numLines);
        cleanup();
        exit(1);
    }
    else
    {
        match(BEGIN);

        // continues to parse until END is read
        while(lookahead != END)
        {
            if(lookahead != BEGIN) // prevents multiple begin statements
            {
                assignStatement();
            }
            if(lookahead == END) // ended the program in success
            {
                printf("success\n");
                printList();
                cleanup();
                exit(0);
            }
        }
    }
}

// looks for identifier and '='
int assignStatement()
{
    match(ID);
    if (lookahead != '=')
    {
        printf("Line %d error: expecting '='\n", numLines);
        exit(1);
    }
    else
    {
        match(lookahead);
        expression();
        match(';');
    }
}

// looks for term followed by '+' or '-'
void expression()
{
    term();
    while(lookahead == '+' || lookahead == '-')
    {
        match(lookahead);
        term();
    }
}

// looks for '*' or '/'
void term()
{
    factor();
    while(lookahead == '*' || lookahead == '/')
    {
        match(lookahead);
        factor();
    }
}

// looks for identifier, number, or parenthesis
void factor()
{
    if(lookahead == ID)
    {
        match(ID);
    }
    else if(lookahead == NUM)
    {
        match(NUM);
    }
    else if(lookahead = '(')
    {
        match('(');
        expression();
        match(')');
    }
    else
    {
        printf("Line %d error: expecting '('\n", numLines);
        exit(1);
    }
}

// checks if the token matches the lookahead type or char
void match(int token)
{
    if(lookahead == token)
    {
        lookahead = lexan();
    }
    else
    {
        printf("Line %d error: expecting ')'\n", numLines);
        exit(1);
    }
}
