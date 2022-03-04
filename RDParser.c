/***************************************************************
  Student Name: Collin Lowing
  File Name: RDParser.c
  Project 2

  parses a statement found in lexical analysis
***************************************************************/

#include "RDParser.h"

int lookahead;
char* identifier;
char operator;
char regArray[10][256];
char opArray[10];
int reg = 0;
int op = 0;


// starts the parsing and lexical analysis
void parse()
{
    // get first token
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
                initializeStatement();
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

/*void statement()
{
    if(lookahead == PRIMITIVE)
    {
        initializeStatement();
    }
    else if(lookahead == ID)
    {
        assignStatement();
    }
    else

}*/

void initializeStatement()
{

    // if primitive type
    if(lookahead =! PRIMITIVE)
    {
        //printf("%d\n",lookahead);
        assignStatement();
    }
    else
    {
        printf("%d\n",lookahead);
        match(PRIMITIVE);
        printf("%d\n",lookahead);
        // next has to be identifier
        if (lookahead != ID)
        {
            printf("Line %d error: expecting identifier\n", numLines);
            cleanup();
            exit(1);
        }
        else
        {
            match(ID);
            // if next token is ',' keep getting ID until ',' is not ending
            while(lookahead == ',')
            {
                match(lookahead);
                if(lookahead != ID)
                {
                    printf("Line %d error: expecting identifier\n", numLines);
                    cleanup();
                    exit(1);
                }
                else
                {
                    match(ID);
                }
            }
        }
    }
}

// looks for identifier and '='
void assignStatement() // changed int to void
{
    // checks if identifier is initialized
    if(lookup(getID()) == NOT_FOUND)
    {
        printf("Line %d error: identifier %s is not initialized\n", numLines, getID());
        cleanup();
        exit(1);
    }

    match(ID);
    if (lookahead != '=')
    {
        printf("Line %d error: expecting '='\n", numLines);
        cleanup();
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
        // store operator
        opArray[op] = lookahead;
        op++;

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
        opArray[op] = lookahead;
        op++;

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
        // load register with identifier
        strcpy(regArray[reg], getID());
        reg++;
        match(ID);
    }
    else if(lookahead == NUM)
    {
        // load register with number
        strcpy(regArray[reg], getID());
        reg++;
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
        cleanup();
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
        cleanup();
        exit(1);
    }
}

void performOperation()
{

    // write out register assigned by identifier or number
    for(int i = 0; i < reg; i++)
    {
        fprintf(output, "R%d = %s\n", i, regArray[i]);
    }

    if(op > 0)
    {
        for(int j = op-1; j > 0; j--)
        {
            fprintf(output, "R%d = R%d %c R%d\n", j, j, opArray[j], j+1);
        }
    }

    // write out first register <operator> second register
    fprintf(output, "*****[");
    for(int i = 0; i < reg; i++)
    {
        fprintf(output, "%s,", regArray[i]);
    }
    for(int j = 0; j < op; j++)
    {
        fprintf(output, "%c,", opArray[j]);
    }
    fprintf(output, "]*****\n");

    reg = 0;
    op = 0;
}

char* getID()
{
    struct node* first = getHead();
    return first->symbol;
}