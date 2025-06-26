#ifndef LINKED_H
#define LINKED_H

// TODO Make a generic for user to choose different data types
//      Ways to solve this problem:
//      1. Macro
//      2. Union
//      3. Enums

#include <stdint.h>

typedef struct node node;

struct node
{
  intptr_t data_;
  struct node *next;
};

typedef struct
{
  node *head_;
  node *tail_;
} linkedList;

#endif // !LINKED_H
