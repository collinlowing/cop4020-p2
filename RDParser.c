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
char* identifier;
int number1;
int number2;
char operator;
int reg = 0; // register counter
int result;

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

        // reset parenthesis counters
        paraLeft = 0;
        paraRight = 0;

        match(';');
    }
}

// looks for term followed by '+' or '-'
void expression()
{
    term();
    while(lookahead == '+' || lookahead == '-')
    {
        // store operator
        insert(OPERATOR, lookahead);
        match(lookahead);
        term();
        // perform operation with both operands
        performOperation();
    }
}

// looks for '*' or '/'
void term()
{
    factor();
    while(lookahead == '*' || lookahead == '/')
    {
        // store operator
        insert(OPERATOR, lookahead);
        match(lookahead);
        factor();
        // perform operation with both operands
        performOperation();
    }
}

// looks for identifier, number, or parenthesis
void factor()
{
    if(lookahead == ID)
    {
        // load register
        match(ID);
    }
    else if(lookahead == NUM)
    {
        // load register
        match(NUM);
    }
    else if(lookahead = '(')
    {
        paraLeft++;
        if(paraRight > 0)
        {
            reg++;
        }
        match('(');
        expression();

        paraRight++;
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

void storeID(char* id)
{
    identifier = id;
}

void storeNUM(char* num)
{
    // convert num to int value
    int i = atoi(num);
    if(number1 == 0;)
    {
        number1 = i;
    }
    else if (number2 == 0;)
    {
        number2 = i;
    }
}

void storeOperator(char op)
{
    operator = op;
}

void performOperation()
{
    // copy linked list current pointer

    // get next node from linked list

    // write out register assigned by identifier or number

    reg++;
    // repeat until operator

    // write out first register <operator> second register

    if(paraLeft > paraRight)
    {
        // write out register <operator> register again
    }
    reg = 0;
}
