/***************************************************************
  Student Name: Collin Lowing
  File Name: LexicalAnalyzer.h
  Project 2

  perform lexical analysis on a file
***************************************************************/

#ifndef COP4020_LEXICALANALYZER_H
#define COP4020_LEXICALANALYZER_H

#include <ctype.h>
#include <string.h>
#include "LinkedList.h"
#include "RDParser.h"

#define MAX_STR_LENGTH 256

#define ID 300
#define NUM 301
#define OPERATOR 302
#define PRIMITIVE 303
#define BEGIN 400
#define END 401
#define NOT_FOUND -1

extern int numLines;
extern int type;
extern FILE * input;
extern char ch;
extern char* fName;
extern char numLexeme[MAX_STR_LENGTH];
extern char idLexeme[MAX_STR_LENGTH];

void init(char * filename);
int lookup(char* lexeme);
int lexan();
void append(char * str, char c);
void cleanup();

#endif //COP4020_LEXICALANALYZER_H
