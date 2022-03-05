/***************************************************************
  Student Name: Collin Lowing
  File Name: RDParser.h
  Project 2

  parses a statement found in lexical analysis
***************************************************************/

#ifndef COP4020_RDPARSER_H
#define COP4020_RDPARSER_H

#include "LexicalAnalyzer.h"
#include "LinkedList.h"
#include<stdio.h>
#include<stdlib.h>

extern int lookahead;
extern char* identifier;
extern char operator;
extern char regArray[10][256]; // stores registers
extern char opArray[10]; // stores operator chars
extern int reg; // register counter
extern int op; // operator counter
extern FILE * output;

void parse();
void initOutput();
void statement();
void initializeStatement();
void assignStatement();
void match(int token);
void factor();
void expression();
void term();
void performOperation();
void printList();
void cleanup();

#endif //COP4020_RDPARSER_H
