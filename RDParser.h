/***************************************************************
  Student Name: Collin Lowing
  File Name: RDParser.h
  Project 2

  parses a statement found in lexical analysis
***************************************************************/

#ifndef COP4020_P1_RDPARSER_H
#define COP4020_P1_RDPARSER_H

#include "LexicalAnalyzer.h"
#include "LinkedList.h"
#include<stdio.h>
#include<stdlib.h>

extern int lookahead;
extern int paraLeft;
extern int paraRight;

void parse();
int assignStatement();
void match(int token);
void factor();
void expression();
void term();
void storeID(char* id);
void storeNUM(char* num);
void storeOperator(char op);
void performOperation();

#endif //COP4020_P1_RDPARSER_H
