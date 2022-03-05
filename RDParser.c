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
FILE * output = NULL;

// starts the parsing and lexical analysis
void parse()
{
    initOutput();
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
                statement();
            }
            if(lookahead == END) // ended the program in success
            {
                printf("success\n");
                //printList();
                cleanup();
                exit(0);
            }
        }
    }
}

void initOutput()
{
    // init file output
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
    }
}

// intermediate
void statement()
{
    if(lookahead == PRIMITIVE)
    {
        initializeStatement();
    }
    else
    {
        assignStatement();
    }
}

// handles initialization statements
void initializeStatement()
{
    match(PRIMITIVE);
    if(lookahead != ID)
    {
        printf("Line %d error: expecting identifier\n", numLines);
        cleanup();
        exit(1);
    }
    else
    {
        if(lookup(idLexeme) != NOT_FOUND)
        {
            printf("Line %d error: redefinition of identifier\n", numLines);
            cleanup();
            exit(1);
        }
        // write register to file
        fprintf(output, "R%d = %s\n", reg, idLexeme);
        strcpy(regArray[reg], idLexeme);
        reg++;
        // insert into list
        insert(ID, idLexeme);
        match(ID);
        while(lookahead == ',')
        {
            match(',');
            if(lookahead != ID)
            {
                printf("Line %d error: expecting identifier after ','\n", numLines);
                cleanup();
                exit(1);
            }
            else
            {
                if(lookup(idLexeme) != NOT_FOUND)
                {
                    printf("Line %d error: redefinition of identifier\n", numLines);
                    cleanup();
                    exit(1);
                }

                // load register with identifier
                fprintf(output, "R%d = %s\n", reg, idLexeme);
                strcpy(regArray[reg], idLexeme);
                reg++;

                insert(ID, idLexeme);
                match(ID);
            }
        }
        match(';');
    }
}

// looks for identifier and '='
void assignStatement()
{
    if(lookup(idLexeme) == NOT_FOUND)
    {
        printf("Line %d error: identifier %s is not initialized\n", numLines, idLexeme);
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
        printf("op = %c\n", opArray[op]);
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
        printf("op = %c\n", opArray[op]);
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
    if(lookahead == ID) {
        if (lookup(idLexeme) == NOT_FOUND)
        {
            printf("Line %d error: identifier %s is not initialized\n", numLines, idLexeme);
            cleanup();
            exit(1);
        }

        match(ID);
    }
    else if(lookahead == NUM)
    {
        printf("numLexeme = %s\n",numLexeme);
        // load register with number
        fprintf(output, "R%d = %s\n", reg, numLexeme);
        strcpy(regArray[reg], numLexeme);
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
    fprintf(output, "R%d = R%d %c R%d\n", reg-reg, reg-reg+1, opArray[op-1], op-1);

    printList();

    /*// empty list
    while(!isEmpty()) {
        deleteFirst();
    }*/

    /*reg = 0;
    op = 0;*/
}

// print the list symbols
void printList() {
    struct node *ptr = head;
    //printf("Identifiers: ");

    // write out ending line with all identifiers and operators in list
    fprintf(output, "*****[");
    while(ptr != NULL) {
        fprintf(output, "%s,", ptr->symbol);
        ptr = ptr->next;
    }
    int i = 0;
    for(; i < op-1; i++)
    {
        fprintf(output, "%c,", opArray[i]);
    }
    fprintf(output, "%c", opArray[i]);
    fprintf(output, "]*****\n");

    //printf("\n");
}

// cleanup pointers to prevent memory leak
void cleanup()
{
    while(!isEmpty()) {
        deleteFirst();
    }

    fclose(input);
    fclose(output);
}