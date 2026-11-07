
#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    int data;
    struct node *link;
} Dlist;

Dlist *insert_first(Dlist *head, int digit);
Dlist *insert_last(Dlist *head, int digit);
Dlist *create_list(const char *num);
void free_list(Dlist *head);
void print_number(const Dlist *head);
int compare_lists(const Dlist *a, const Dlist *b);

Dlist *addition(const Dlist *a, const Dlist *b);
Dlist *subtraction(const Dlist *a, const Dlist *b);
Dlist *multiplication(const Dlist *a, const Dlist *b);
Dlist *division(const Dlist *a, const Dlist *b);

#endif
