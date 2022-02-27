/***************************************************************
  Student Name: Collin Lowing
  File Name: LinkedList.c
  Project 2

  store identifiers
***************************************************************/

#include "LinkedList.h"

struct node *head = NULL;       // starting pointer for list
struct node *current = NULL;    // current place in list

// print the list symbols
void printList() {
    struct node *ptr = head;
    printf("Identifiers: ");

    while(ptr != NULL) {
        printf("%s ", ptr->symbol);
        ptr = ptr->next;
    }

    printf("\n");
}

// insert link at the first location
void insert(int key, char* symbol) {
    // create a link
    struct node *link = (struct node*) malloc(sizeof(struct node));

    link->key = key;
    strcpy(link->symbol, symbol); // copy the string to new pointer

    // point it to old first node
    link->next = head;

    // point first to new first node
    head = link;
}

// delete first item in the list
void deleteFirst() {

    // copy head pointer
    struct node *temp = head;

    // change head to its next pointer
    head = head->next;

    // free memory for original head pointer
    free(temp);
}

// check if list is empty
bool isEmpty() {
    return head == NULL;
}

// find a node with symbol array
struct node* find(char symbol[256]) {

    // start from the first pointer
    struct node* current = head;

    // if list is empty
    if(head == NULL) {
        return NULL;
    }

    // iterate through list until symbol matches
    while(strcmp(current->symbol, symbol) != 0) {
        // if it is last node
        if(current->next == NULL) {
            return NULL;
        } else {
            // go to next node in list
            current = current->next;
        }
    }

    // if symbol found, return the current node
    return current;
}
