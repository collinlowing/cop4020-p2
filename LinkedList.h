/***************************************************************
  Student Name: Collin Lowing
  File Name: LinkedList.h
  Project 2

  store identifiers
***************************************************************/

#ifndef COP4020_P1_LINKEDLIST_H
#define COP4020_P1_LINKEDLIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    char symbol[256];
    int key;
    struct node *next;
};

extern struct node *head;
extern struct node *current;

void printList();
void insert(int key, char symbol[256]);
void deleteFirst();
bool isEmpty();
struct node* find(char* symbol);

#endif //COP4020_P1_LINKEDLIST_H
